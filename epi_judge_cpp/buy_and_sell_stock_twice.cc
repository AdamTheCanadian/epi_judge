#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {
  double max_profit = 0.0;
  std::vector<double> first_pass(prices.size(), 0);
  double min_price = 1.0e6;

  for (int i = 0; i < prices.size(); i++) {
    if (prices[i] < min_price) {
      min_price = prices[i];
    }
    double price_diff_today = prices[i] - min_price;
    if (price_diff_today > max_profit) {
      max_profit = price_diff_today;
    }
    // For this day, this is the maximum profit found thus far
    first_pass[i] = max_profit;
  }

  double max_price = -1.0e6;
  for (int i = prices.size() - 1; i > 0; --i) {
    if (prices[i] > max_price) {
      max_price = prices[i];
    }
    double total_profit_today = max_price - prices[i] + first_pass[i];
    if (total_profit_today > max_profit) {
      max_profit = total_profit_today;
    }
  }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
