#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  
  int min_index = 0;
  double min_price = 1.0e6;
  double max_profit = 0.0;
  for (int i = 0; i < prices.size(); i++) {
    double diff_today = prices[i] - min_price;
    if (diff_today > max_profit) {
      max_profit = diff_today;
    }
    // Do we have a new minimum found, if so update
    if (prices[i] < min_price) {
      min_price = prices[i];
    }
  }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
