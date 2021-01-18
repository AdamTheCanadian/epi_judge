#include <array>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
enum class Color { kRed, kWhite, kBlue };

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
  vector<Color>&A = *A_ptr;
  Color pivot = A[pivot_index];
  int smaller = 0;
  for (int i = 0; i < A.size(); ++i) {
    if (A[i] < pivot) {
      std::swap(A[i], A[smaller++]);
    }
  }
  int larger = A.size() - 1;
  for (int i = A.size() - 1; i >= 0; --i) {
    if (A[i] > pivot) {
      std::swap(A[i], A[larger--]);
    }
  }
}

void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}

/* Crude implementation 1 that creates three vectors for 
  less than, equal to, or greater than the pivot. Then combines
  the vectors at the end

std::vector<Color> less, equal, greater;
  const auto& pivot_value = A_ptr->at(pivot_index);
  for (int i = 0; i < A_ptr->size(); i++) {
    if (A_ptr->at(i) == pivot_value) {
      equal.push_back(A_ptr->at(i));
    }
    else if (A_ptr->at(i) > pivot_value) {
      greater.push_back(A_ptr->at(i));
    }
    else {
      less.push_back(A_ptr->at(i));
    }
  }
  // Combine the vectors
  int index = 0;
  for (auto& s : less) {
    A_ptr->at(index) = s;
    index += 1;
  }
  for (auto& s : equal) {
    A_ptr->at(index) = s;
    index += 1;
  }
  for (auto& s : greater) {
    A_ptr->at(index) = s;
    index += 1;
  }

*/

/* Crude implementation 2, not working

std::vector<Color> less, equal, greater;
  const auto& pivot_value = A_ptr->at(pivot_index);
  std::cout << std::endl;
  std::cout << "Pivot value is " << (int)pivot_value << std::endl;
  // Iterate through the array placing all values smaller than the pivot
  // at the front
  int smaller_index = 0;
  for (int i = 0; i < A_ptr->size(); i++) {
    if (A_ptr->at(i) < pivot_value) {
      std::cout << "Smaller was: " << smaller_index << " i is " << i << std::endl;
      std::swap(A_ptr->at(i), A_ptr->at(smaller_index++));
      for (int j = 0; j < A_ptr->size(); j++) {
        std::cout << (int)A_ptr->at(j) << " ";
      }
      std::cout << std::endl;
      std::cout << "Smaller is now " << smaller_index << std::endl;
    }
  }

  int larger_index = A_ptr->size() - 1;
  for (int i = A_ptr->size() - 1; i >= 0; i--) {
    if (A_ptr->at(i) > pivot_value) {
      std::swap(A_ptr->at(i), A_ptr->at(larger_index--));
      std::cout << "Larger is now " << larger_index << std::endl;
    }
  }
  for (int i = 0; i < A_ptr->size(); i++) {
    std::cout << (int)A_ptr->at(i) << " ";
  }
  std::cout << std::endl;
  return;

  */