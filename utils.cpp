#include "utils.hpp"
#include <format>

namespace FJAUtils {

bool hasDuplicates(std::vector<int>& v) {
  std::sort(v.begin(), v.end());
  auto it = std::adjacent_find(v.begin(), v.end());
  return it != v.end();
}

void displayTiming(const std::vector<int>& input, long long dequeTime, long long vectorTime) {
  std::cout << std::format("Time to process a range of {} elements with std::deque : {} us\n",
                      input.size(), dequeTime);
  std::cout << std::format("Time to process a range of {} elements with std::vector: {} us\n",
                      input.size(), vectorTime);
}

} // namespace FJAUtils
