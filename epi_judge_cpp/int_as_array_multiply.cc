#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> Multiply(vector<int> num1, vector<int> num2) {
  // Determine the final sign of the number
  int sign = 1;
  if (num1.front() < 0 && num2.front() > 0) {
    sign = -1;
  }
  else if (num1.front() > 0 && num2.front() < 0) {
    sign = -1;
  }
  num1.front() = abs(num1.front());
  num2.front() = abs(num2.front());
  // Initialize the return to all 0's. We may not use all the values
  std::vector<int> result(num1.size() + num2.size(), 0);
  for (int i = num1.size() - 1; i >= 0; i--) {
    for (int j = num2.size() - 1; j >= 0; j--) {
      result[i + j + 1] += num1[i] * num2[j];
      result[i + j] += result[i + j + 1] / 10;
      result[i + j + 1] %= 10;
    }
  }
  // while(result.front() == 0) {
  //   result.erase(result.begin() + 0);
  // }
  result = {
    std::find_if_not(std::begin(result), std::end(result), [](int a) {return a == 0;}), std::end(result)};
  if (result.empty()) {
    return {0};
  }
  result.front() *= sign;
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
