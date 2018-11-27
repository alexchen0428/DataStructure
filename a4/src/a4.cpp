#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <getopt.h>
#include <vector>
#include "trade.h"

bool v_flag = false, m_flag = false, p_flag = false, t_flag = false, g_flag = false;
std::vector<std::string> tttList;

extern unsigned currentTimeStamp;

Trade& trade = Trade::getInstance();

void getoptions(const int &argc, char **argv) {
    static option long_options[] = {
          {"verbose",   no_argument,       0, 'v'},
          {"median",    no_argument,       0, 'm'},
          {"midpoint",  no_argument,       0, 'p'},
          {"transfers", no_argument,       0, 't'},
          {"ttt",       required_argument, 0, 'g'},
          {0, 0, 0, 0}
    };

    int option_index = 0, c = -1;
    while ((c = getopt_long(argc, argv, "vmptg:", long_options, &option_index)) != -1) {
        switch(c) {
            case 'v':
                v_flag = 1; break;
            case 'm':
                m_flag = 1; break;
            case 'p':
                p_flag = 1; break;
            case 't':
                t_flag = 1; break;
            case 'g':
                g_flag = 1;
                tttList.emplace_back(optarg); break;
            default: break;
        }
    }
}

void execute() {
    unsigned id = 0;
    string cmd;
    while (getline(std::cin, cmd) && !cmd.empty()) {
        std::istringstream sin(cmd);
        int duration;
        unsigned timeStamp, price, quantity;
        std::string name, sell_buy, equity;
        char nop;
        sin >> timeStamp >> name >> sell_buy >> equity >> nop >> price >> nop >> quantity >> duration;
        if (timeStamp != currentTimeStamp) {
            if (m_flag) trade.medianPrint();
            if (p_flag) trade.midpointPrint();
            currentTimeStamp = timeStamp;
        }
        if (sell_buy == "SELL") {
            trade.sellerMatch(id++, timeStamp, std::move(name), std::move(equity), price, quantity, duration);
        } else {
            trade.buyerMatch(id++, timeStamp, std::move(name), std::move(equity), price, quantity, duration);
        }
    }
    if (m_flag) trade.medianPrint();
    if (p_flag) trade.midpointPrint();
    trade.summary();
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    getoptions(argc, argv);
    trade.setTTTList(std::move(tttList));
    trade.setFlag(v_flag, m_flag, p_flag, t_flag, g_flag);
    execute();
    return 0;
}