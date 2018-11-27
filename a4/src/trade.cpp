#include <iostream>
#include <algorithm>
#include "trade.h"
#define log_v(buyer, q, equity, seller, p) std::cout << buyer << " purchased " << q << " shares of " << equity << " from " << seller << " for $" << p << "/share\n"

#define expired(x) (x->duration > 0 && x->duration + x->timeStamp <= currentTimeStamp)

#define log_p()\
if (equityMap.find(equity) == equityMap.end()) {\
    equityMap[equity] = true;\
    equityList.insert(equity);\
}
#define log_g(x)\
tttMap[equity].emplace_back(std::make_shared<tttOrder>(x, price, timeStamp))

#define log_m() pricemedian[equity].insert(p)

const unsigned INF = (1 << 30);

std::unique_ptr<Trade> Trade::instance = nullptr;

unsigned currentTimeStamp = 0;

Trade &Trade::getInstance() {
    if (Trade::instance == nullptr) {
        instance = std::unique_ptr<Trade>(new Trade);
    }
    return *instance;
}

void Trade::PriceMedian::insert(unsigned x) {
    if (n&1) { // odd
        if (x >= maxheap.top()) minheap.push(x);
        else {
            unsigned vic = maxheap.top();
            maxheap.pop();
            minheap.push(vic);
            maxheap.push(x);
        }
    } else { // even
        if (n == 0 || x <= minheap.top()) maxheap.push(x);
        else {
            unsigned vic = minheap.top();
            minheap.pop();
            maxheap.push(vic);
            minheap.push(x);
        }
    }
    n++;
}

void Trade::sellerMatch(unsigned id,
                        unsigned timeStamp,
                        string &&name,
                        string &&equity,
                        unsigned price,
                        unsigned quantity,
                        int duration) {
    if (p_flag) log_p();
    if (g_flag) log_g(false);
    auto &buyer = orderBookMap[equity].buyer;
    while (!buyer.empty() && quantity > 0) {
        if (expired(buyer.top())) { // expire
            buyer.pop();
            continue;
        }
        if (buyer.top()->price < price) break; // price not match, the latter buyer price are lower, cannot match anyway

        // do transaction
        unsigned q = std::min(quantity, buyer.top()->quantity);
        unsigned p = buyer.top()->price; // buyer comes first
        unsigned money = (p * q);
        unsigned c_fee = money / 100;
        buyer.top()->quantity -= q;
        quantity -= q;
        //default output
        c_earnings += (c_fee << 1);
        total += money;
        ++trade_num;
        share_num += q;

        // options
        if (v_flag) log_v(buyer.top()->name, q, equity, name, p);
        if (m_flag) log_m();
        if (t_flag) {
            transfers[name].sold += q;
            transfers[name].netValue += money;
            transfers[buyer.top()->name].bought += q;
            transfers[buyer.top()->name].netValue -= money;
        }
        // pop
        if (buyer.top()->quantity == 0) buyer.pop();
    }

    if (quantity > 0 && duration != 0) { // add to book
        orderBookMap[equity].seller.emplace(std::make_shared<client>(id, timeStamp, move(name), move(equity), price, quantity, duration));
    }
}

void Trade::buyerMatch(unsigned id,
                        unsigned timeStamp,
                        string &&name,
                        string &&equity,
                        unsigned price,
                        unsigned quantity,
                        int duration) {
    if (p_flag) log_p();
    if (g_flag) log_g(true); 
    auto &seller = orderBookMap[equity].seller;
    while (!seller.empty() && quantity > 0) {
        if (expired(seller.top())) { // expire
            seller.pop();
            continue;
        }
        if (seller.top()->price > price) break; // price not match, the latter seller price are higher, cannot match anyway

        // do transaction
        unsigned q = std::min(quantity, seller.top()->quantity);
        unsigned p = seller.top()->price; // seller comes first
        unsigned money = (p * q);
        unsigned c_fee = money / 100;
        seller.top()->quantity -= q;
        quantity -= q;
        //default output
        c_earnings += (c_fee << 1);
        total += money;
        ++trade_num;
        share_num += q;

        // options
        if (v_flag) log_v(name, q, equity, seller.top()->name, p);
        if (m_flag) log_m();
        if (t_flag) {
            transfers[name].bought += q;
            transfers[name].netValue -= money;
            transfers[seller.top()->name].sold += q;
            transfers[seller.top()->name].netValue += money;
        }
        // pop
        if (seller.top()->quantity == 0) seller.pop();
    }

    if (quantity > 0 && duration != 0) { // add to book
        orderBookMap[equity].buyer.emplace(std::make_shared<client>(id, timeStamp, move(name), move(equity), price, quantity, duration));
    }
}

void Trade::medianPrint() const {
    for (auto &equity : pricemedian) {
        std::cout << "Median match price of " << equity.first << " at time " << currentTimeStamp << " is $" << equity.second.getMedian() << '\n';
    }
}

void Trade::midpointPrint() {
    for (auto &equity : equityList) {
        auto &buyer = orderBookMap[equity].buyer;
        auto &seller = orderBookMap[equity].seller;
        while (!buyer.empty() && expired(buyer.top())) buyer.pop();
        while (!seller.empty() && expired(seller.top())) seller.pop();
        std:: cout << "Midpoint of " << equity << " at time " << currentTimeStamp << " is";
        if (buyer.empty() || seller.empty()) {
            std::cout << " undefined\n";
        } else {
            std::cout << " $" << ((buyer.top()->price + seller.top()->price) >> 1) << '\n';
        }
    }
}

void Trade::summary() {
    std::cout << "---End of Day---\n";
    std::cout << "Commission Earnings: $" << c_earnings << '\n';
    std::cout << "Total Amount of Money Transferred: $" << total << '\n';
    std::cout << "Number of Completed Trades: " << trade_num << '\n';
    std::cout << "Number of Shares Traded: " << share_num << '\n';
    if (t_flag) transferPrint();
    if (g_flag) tttPrint();
}

void Trade::transferPrint() {
    for (auto &info : transfers) {
        std::cout << info.first << " bought " << info.second.bought << " and sold " << info.second.sold << " for a net transfer of $" << info.second.netValue << '\n';
    }
}

void Trade::tttPrint() {
    for (auto &equity : tttList) {
        auto &orders = tttMap[equity]; // vector of tttOrder::Ptr
        int ts1_cand, ts1 = -1, ts2 = -1;
        int profit = -INF;
        unsigned seller_price = INF;
        bool has_seller = false;
        for (size_t i = 0; i < orders.size(); ++i) {
            if (!orders[i]->isBuy) { // seller
                has_seller = true;
                if (orders[i]->price < seller_price) { // update seller price
                    ts1_cand = orders[i]->timeStamp;
                    seller_price = orders[i]->price;
                }
            } else { // buyer
                if (has_seller && (signed)(orders[i]->price - seller_price) > profit) { // new profit
                    ts1 = ts1_cand;
                    ts2 = orders[i]->timeStamp;
                    profit = orders[i]->price - seller_price;
                }
            }
        }
        std::cout << "Time travelers would buy " << equity << " at time: " << ts1 << " and sell it at time: " << ts2 << '\n';
    }
}
