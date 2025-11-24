#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

namespace FJAUtils {

bool hasDuplicates(std::vector<int>& v);

template<typename Container>
void displaySequence(const Container& container, bool isSorted);

void displayTiming(const std::vector<int>& input, long long dequeTime, long long vectorTime);

template<typename Container>
void displaySequence(const Container& container, bool isSorted) {
  std::cout << (isSorted ? "After:  " : "Before: ");

  for (size_t i = 0; i < container.size(); ++i) {
  std::cout << container[i];
  if (i < container.size() - 1) {
    std::cout << " ";
  }
  }
  std::cout << std::endl;
}

} // namespace FJAUtils
