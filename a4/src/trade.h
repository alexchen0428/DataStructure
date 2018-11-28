#ifndef _TRADE_H_
#define _TRADE_H_

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
#include <map>
#include <memory>

using std::unordered_map;
using std::map;
using std::multimap;
using std::string;
using std::priority_queue;
using std::vector;
using std::move;
using std::unordered_set;
using std::set;

class Trade {
private:
    typedef string EquityNameType;
    struct client {
        typedef std::shared_ptr<client> Ptr;
        unsigned id, timeStamp;
        string name;
        EquityNameType equity;
        unsigned price;
        unsigned quantity;
        int duration;
        client(unsigned &id, unsigned &timeStamp, string &&name, string &&equity, unsigned &price, unsigned &quantity, int &duration): id(id), timeStamp(timeStamp), name(move(name)), equity(move(equity)), price(price), quantity(quantity), duration(duration) {}
    };

    struct greater_t {
        bool operator()(const client::Ptr x, const client::Ptr y) const {
            if (x->price == y->price) return x->id > y->id;
            return x->price > y->price;
        }
    };

    struct less_t {
        bool operator()(const client::Ptr x, const client::Ptr y) const {
            if (x->price == y->price) return x->id > y->id;
            return x->price < y->price;
        }
    };

    struct PriceMedian {
        unsigned n;
        priority_queue<unsigned, vector<unsigned>, std::greater<unsigned> > minheap;
        priority_queue<unsigned, vector<unsigned>,    std::less<unsigned> > maxheap;
        PriceMedian(): n(0) {}
        void insert(unsigned x);
        unsigned getMedian() const {return (n&1) ? maxheap.top() : ((maxheap.top()+minheap.top()) >> 1);}
    };

    struct TransferInfo {
        unsigned bought, sold;
        int netValue;
        TransferInfo() {bought = sold = 0; netValue = 0;}
    };

    struct orderBook {
        priority_queue<client::Ptr, vector<client::Ptr>, greater_t> seller; // seller, price increasing
        priority_queue<client::Ptr, vector<client::Ptr>, less_t> buyer; // buyer, price decreasing
    };

    struct tttOrder{
        typedef std::shared_ptr<tttOrder> Ptr;
        bool isBuy;
        unsigned price, timeStamp;
        tttOrder(bool isBuy, unsigned &price, unsigned &timeStamp): isBuy(isBuy), price(price), timeStamp(timeStamp) {}
    };

    unordered_map<EquityNameType, orderBook> orderBookMap;

    unordered_set<EquityNameType> equitySet;
    set<EquityNameType> equityList; // for midpoint output

    unordered_set<string> nameSet;
    map<string, TransferInfo> transfers; // for transfers

    map<EquityNameType, PriceMedian> pricemedian; // EquityNameType dictionary order

    vector<EquityNameType> tttList; // for ttt

    unordered_set<EquityNameType> tttEquitySet;

    unordered_map<EquityNameType, vector<tttOrder::Ptr> > tttMap; // from string to order list

    unsigned c_earnings = 0, total = 0, trade_num = 0, share_num = 0;

    bool v_flag, m_flag, p_flag, t_flag, g_flag;

    void transferPrint();

    void tttPrint();

private:
    static std::unique_ptr<Trade> instance;
    Trade() = default;

public:
    Trade &operator=(const Trade &) = delete;
	Trade &operator=(Trade &&) = delete;
	Trade(const Trade &) = delete;
	Trade(Trade &&) = delete;
	~Trade() = default;

    static Trade &getInstance();

    void setTTTList(vector<string> &&x, unordered_set<string> &&y) {tttList = move(x); tttEquitySet = move(y);}

    void setFlag(const bool &vflag, const bool &mflag, const bool &pflag, const bool &tflag, const bool &gflag) {
        v_flag = vflag;
        m_flag = mflag;
        p_flag = pflag;
        t_flag = tflag;
        g_flag = gflag;
    }

    void sellerMatch(unsigned id,
                     unsigned timeStamp,
                     string &&name,
                     string &&equity,
                     unsigned price,
                     unsigned quantity,
                     int duration);
    
    void buyerMatch(unsigned id,
                     unsigned timeStamp,
                     string &&name,
                     string &&equity,
                     unsigned price,
                     unsigned quantity,
                     int duration);
    
    void medianPrint() const;

    void midpointPrint();

    void summary();
};

#endif