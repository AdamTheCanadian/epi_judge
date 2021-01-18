#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {
  
  int sell_index = 0;
  double min_price = 1.0e6;
  double max_profit1 = 0.0;
  for (int i = 0; i < prices.size(); i++) {
    double diff_today = prices[i] - min_price;
    if (diff_today > max_profit1) {
      max_profit1 = diff_today;
      sell_index = i;
    }
    // Do we have a new minimum found, if so update
    if (prices[i] < min_price) {
      min_price = prices[i];
    }
  }
  min_price = 1.0e6;
  double max_profit2 = 0.0;
  for (int i = sell_index; i < prices.size(); i++) {
    double diff_today = prices[i] - min_price;
    if (diff_today > max_profit2) {
      max_profit2 = diff_today;
      sell_index = i;
    }
    // Do we have a new minimum found, if so update
    if (prices[i] < min_price) {
      min_price = prices[i];
    }
  }
  return max_profit1 + max_profit2;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
