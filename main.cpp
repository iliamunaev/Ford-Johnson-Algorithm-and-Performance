#include "FJA.hpp"
#include "utils.hpp"

using namespace FJASort;
using namespace FJAUtils;

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <functional>
#include <format>

std::pair<bool, std::vector<std::string>> parseCommandLineArguments(int argc, char** argv) {
  bool useThreads = false;
  std::vector<std::string> args;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-t" || arg == "--threaded") {
      useThreads = true;
    } else {
      args.push_back(arg);
    }
  }
  return {useThreads, args};
}

void displayUsage(char* programName) {
  std::cerr << "Usage: " << programName << " [-t|--threaded] <positive integer> [positive integer ...]" << std::endl;
  std::cerr << "Options:" << std::endl;
  std::cerr << "  -t, --threaded    Run sorting operations concurrently using threads" << std::endl;
  std::cerr << "Example: " << programName << " 3 5 9 7 4" << std::endl;
  std::cerr << "Example: " << programName << " -t 3 5 9 7 4" << std::endl;
}

std::vector<int> validateAndParseInput(const std::vector<std::string>& args) {
  if (args.empty()) {
    throw std::runtime_error("No input arguments provided");
  }

  if (!FJA::validateInput(args)) {
    throw std::runtime_error("Invalid input validation");
  }

  auto input = FJA::parseInput(args);

  std::vector<int> inputCopy = input;
  if (FJAUtils::hasDuplicates(inputCopy)) {
    throw std::runtime_error("Duplicate numbers are not allowed");
  }

  return input;
}

long long runConcurrentSorting(FJA& sorter, const std::vector<int>& input) {
  std::cout << "\n=== Running with threads (concurrent execution) ===" << std::endl;

  auto start = std::chrono::high_resolution_clock::now();

  std::thread dequeThread(&FJA::sortWithDeque, &sorter, std::ref(input));
  std::thread vectorThread(&FJA::sortWithVector, &sorter, std::ref(input));

  dequeThread.join();
  vectorThread.join();

  auto end = std::chrono::high_resolution_clock::now();
  auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

  std::cout << std::format("Total time with threads: {} us\n", totalTime);
  return totalTime;
}

long long runSequentialSorting(FJA& sorter, const std::vector<int>& input) {
  std::cout << "\n=== Running sequentially (no threads) ===" << std::endl;

  auto start = std::chrono::high_resolution_clock::now();

  sorter.sortWithDeque(input);
  sorter.sortWithVector(input);

  auto end = std::chrono::high_resolution_clock::now();
  auto totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

  std::cout << std::format("Total time without threads: {} us\n", totalTime);
  return totalTime;
}

long long runSortingOperations(FJA& sorter, const std::vector<int>& input, bool useThreads) {
  if (useThreads) {
    return runConcurrentSorting(sorter, input);
  } else {
    return runSequentialSorting(sorter, input);
  }
}

void verifyAndDisplayResults(const FJA& sorter, const std::vector<int>& input) {
  bool dequeSorted = std::is_sorted(sorter.getSortedDeque().begin(), sorter.getSortedDeque().end());
  bool vectorSorted = std::is_sorted(sorter.getSortedVector().begin(), sorter.getSortedVector().end());

  std::cout << "\n=== Sorting Verification ===" << std::endl;
  std::cout << (dequeSorted ? "✓ Deque sorting: SUCCESS" : "✗ Deque sorting: FAILED") << std::endl;
  std::cout << (vectorSorted ? "✓ Vector sorting: SUCCESS" : "✗ Vector sorting: FAILED") << std::endl;

  if (!dequeSorted || !vectorSorted) {
    throw std::runtime_error("One or more sorting operations failed");
  }

  std::cout << "\n=== Individual operation times ===" << std::endl;
  FJAUtils::displayTiming(input, sorter.getDequeSortTime(), sorter.getVectorSortTime());

  long long individualTotal = sorter.getDequeSortTime() + sorter.getVectorSortTime();
  std::cout << std::format("Total individual operations time: {} us\n", individualTotal);
}

int main(int argc, char** argv) {
  try {
    auto [useThreads, args] = parseCommandLineArguments(argc, argv);

    if (args.empty()) {
      displayUsage(argv[0]);
      return 1;
    }

    auto input = validateAndParseInput(args);

    FJA sorter;
    runSortingOperations(sorter, input, useThreads);
    verifyAndDisplayResults(sorter, input);

    return 0;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}