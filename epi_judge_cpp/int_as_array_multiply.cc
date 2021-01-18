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
  // Initialize the return to all 0's. We may not use all the values
  std::vector<int> result(num1.size() + num2.size(), 0);
  // TODO - you fill in here.
  /*
     
    123
  x 456
    ---
     18

  */
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
