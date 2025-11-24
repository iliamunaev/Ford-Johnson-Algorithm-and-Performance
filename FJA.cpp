#include "FJA.hpp"
#include "exceptions.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <climits>

using namespace FJASort;

FJA::FJA() : dequeSortTime_(0), vectorSortTime_(0) {}

FJA::~FJA() {}

void FJA::sortWithDeque(const std::vector<int>& input) {
  deque_.assign(input.begin(), input.end());

  auto start = std::chrono::high_resolution_clock::now();
  fordJohnsonSort(deque_);
  auto end = std::chrono::high_resolution_clock::now();

  dequeSortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void FJA::sortWithVector(const std::vector<int>& input) {
  vector_ = input;

  auto start = std::chrono::high_resolution_clock::now();
  fordJohnsonSort(vector_);
  auto end = std::chrono::high_resolution_clock::now();

  vectorSortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

const std::deque<int>& FJA::getSortedDeque() const {
  return deque_;
}

const std::vector<int>& FJA::getSortedVector() const {
  return vector_;
}

long long FJA::getDequeSortTime() const {
  return dequeSortTime_;
}

long long FJA::getVectorSortTime() const {
  return vectorSortTime_;
}

bool FJA::validateInput(const std::vector<std::string>& args) {
  if (args.empty()) {
    throw ValidationError("No input sequence provided");
  }

  for (const auto& arg : args) {
    try {
      isValidPositiveInteger(arg);
    } catch (const ValidationError&) {
      return false;
    }
  }

  return true;
}

bool FJA::isValidPositiveInteger(const std::string& arg) {
  if (arg.empty()) {
    throw ValidationError("Empty argument found");
  }

  if (arg[0] == '-') {
    throw ValidationError("Negative numbers are not allowed");
  }

  for (char c : arg) {
    if (!std::isdigit(c)) {
      throw ValidationError("Invalid character '" + std::string(1, c) + "' in input");
    }
  }

  if (arg.size() > 1 && arg[0] == '0') {
    throw ValidationError("Leading zeros are not allowed");
  }

  return true;
}

std::vector<int> FJA::parseInput(const std::vector<std::string>& args) {
  std::vector<int> result;
  result.reserve(args.size());

  for (const auto& arg : args) {
    try {
      long long value = std::stoll(arg);
      if (value > INT_MAX) {
        throw ParseError("Number too large: " + arg);
      }
      if (value < 0) {
        throw ParseError("Negative number: " + arg);
      }
      result.push_back(static_cast<int>(value));
    } catch (const std::invalid_argument&) {
      throw ParseError("Invalid number format: " + arg);
    } catch (const std::out_of_range&) {
      throw ParseError("Number out of range: " + arg);
    }
  }

  return result;
}

std::vector<size_t> FJA::generateJacobsthalSequence(size_t pairCount) {
  std::vector<size_t> jacobsthal;
  if (pairCount == 0) {
    return jacobsthal;
  }

  jacobsthal.push_back(0);
  if (pairCount == 1){
    return jacobsthal;
  }

  jacobsthal.push_back(1);
  if (pairCount == 2) {
    return jacobsthal;
  }

  size_t currentIndex = 2;
  while (jacobsthal.back() < pairCount) {
    size_t nextValue = jacobsthal[currentIndex-1] + 2 * jacobsthal[currentIndex-2];
    jacobsthal.push_back(nextValue);
    currentIndex++;
  }

  while (!jacobsthal.empty() && jacobsthal.back() >= pairCount) {
    jacobsthal.pop_back();
  }
  if (jacobsthal.empty() || jacobsthal.back() != pairCount) {
    jacobsthal.push_back(pairCount);
  }
  return jacobsthal;
}

void FJA::fordJohnsonSort(std::deque<int>& container) {
  if (container.size() <= 1) {
    return;
  }
  mergeInsertSort(container);
}

void FJA::fordJohnsonSort(std::vector<int>& container) {
  if (container.size() <= 1) {
    return;
  }
  mergeInsertSort(container);
}

template <typename ContainerType>
void FJA::mergeInsertSort(ContainerType& container) {
  size_t elementCount = container.size();

  if (elementCount <= 1) {
    return;
  }
  if (elementCount == 2) {
    sortTwoElements(container);
    return;
  }

  auto [pairs, leftover, hasLeftover] = createSortedPairs(container);
  ContainerType largerElements = extractLargerElements<ContainerType>(pairs);
  mergeInsertSort(largerElements);

  ContainerType mainChain = buildMainChain(largerElements, pairs, leftover, hasLeftover);
  container = mainChain;
}

template <typename ContainerType>
void FJA::sortTwoElements(ContainerType& container) {
  if (container[0] > container[1]) {
    std::swap(container[0], container[1]);
  }
}

template <typename ContainerType>
std::tuple<FJA::PairVector<typename ContainerType::value_type>,
           typename ContainerType::value_type, bool>
FJA::createSortedPairs(const ContainerType& container) {
  FJA::PairVector<typename ContainerType::value_type> pairs;
  typename ContainerType::value_type leftover = 0;
  bool hasLeftover = (container.size() % 2 == 1);
  size_t pairEnd = container.size() - (hasLeftover ? 1 : 0);

  for (size_t i = 0; i < pairEnd; i += 2) {
    typename ContainerType::value_type first = container[i];
    typename ContainerType::value_type second = container[i + 1];

    if (first > second) {
      pairs.push_back({second, first});
    } else {
      pairs.push_back({first, second});
    }
  }

  if (hasLeftover) {
    leftover = container.back();
  }

  return {pairs, leftover, hasLeftover};
}

template <typename ContainerType>
ContainerType FJA::extractLargerElements(const FJA::PairVector<typename ContainerType::value_type>& pairs) {
  ContainerType largerElements;
  for (const auto& pair : pairs) {
    largerElements.push_back(pair.second);
  }

  return largerElements;
}

template <typename ContainerType>
ContainerType FJA::buildMainChain(const ContainerType& largerElements,
                                   const FJA::PairVector<typename ContainerType::value_type>& pairs,
                                   typename ContainerType::value_type leftover,
                                   bool hasLeftover) {
  ContainerType mainChain = largerElements;

  insertSmallerElements(mainChain, pairs);

  if (hasLeftover) {
    insertLeftoverElement(mainChain, leftover);
  }

  return mainChain;
}

template <typename ContainerType>
void FJA::insertSmallerElements(ContainerType& mainChain,
                                 const FJA::PairVector<typename ContainerType::value_type>& pairs) {
  if (pairs.empty()) {
    return;
  }

  std::vector<size_t> jacobsthal = generateJacobsthalSequence(pairs.size());
  std::vector<bool> inserted(pairs.size(), false);

  for (size_t i = 1; i < jacobsthal.size(); ++i) {
    size_t start = jacobsthal[i-1];
    size_t end = jacobsthal[i];

    for (size_t pairIndex = end; pairIndex > start; --pairIndex) {
      size_t actualIndex = pairIndex - 1;
      if (actualIndex < pairs.size() && !inserted[actualIndex]) {
        typename ContainerType::value_type smaller = pairs[actualIndex].first;
        size_t insertPosition = binarySearch(mainChain, smaller, 0, mainChain.size());
        mainChain.insert(mainChain.begin() + insertPosition, smaller);
        inserted[actualIndex] = true;
      }
    }
  }

  for (size_t pairIndex = 0; pairIndex < pairs.size(); ++pairIndex) {
    if (!inserted[pairIndex]) {
      typename ContainerType::value_type smaller = pairs[pairIndex].first;
      size_t insertPosition = binarySearch(mainChain, smaller, 0, mainChain.size());
      mainChain.insert(mainChain.begin() + insertPosition, smaller);
    }
  }
}

template <typename ContainerType>
void FJA::insertLeftoverElement(ContainerType& mainChain, typename ContainerType::value_type leftover) {
  size_t insertPosition = binarySearch(mainChain, leftover, 0, mainChain.size());
  mainChain.insert(mainChain.begin() + insertPosition, leftover);
}

template <typename ContainerType>
size_t FJA::binarySearch(const ContainerType& container, typename ContainerType::value_type value, size_t low, size_t high) {
  while (low < high) {
    size_t mid = low + (high - low) / 2;

    if (container[mid] < value) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }

  return low;
}

template <typename ContainerType>
void FJA::binaryInsert(ContainerType& container, typename ContainerType::value_type value, size_t end) {
  size_t pos = binarySearch(container, value, 0, end);
  container.insert(container.begin() + pos, value);
}
