#pragma once

#include <deque>
#include <vector>
#include <string>
#include <chrono>

namespace FJASort {

/**
 * @brief Ford-Johnson Algorithm (Merge-Insertion Sort) implementation
 *
 * This class implements the Ford-Johnson algorithm, also known as merge-insertion sort,
 * which is an efficient sorting algorithm that combines the benefits of merge sort and
 * insertion sort. It achieves optimal performance for small to medium-sized datasets
 * by leveraging Jacobsthal numbers for efficient element insertion.
 *
 * The algorithm works by:
 * 1. Creating sorted pairs from the input
 * 2. Recursively sorting the larger elements from each pair
 * 3. Building a main chain and inserting smaller elements using binary search
 * 4. Following the Jacobsthal sequence for optimal insertion order
 *
 * Time Complexity: O(n log n) in practice, though theoretically O(n²) in worst case
 * Space Complexity: O(n) due to temporary containers
 */
class FJA {
  public:
    
    template <typename T>
    using ValuePair = std::pair<T, T>;

    template <typename T>
    using PairVector = std::vector<ValuePair<T>>;
    
    FJA();
    FJA(const FJA& other) = delete;
    FJA& operator=(const FJA& other) = delete;
    ~FJA();

    void sortWithDeque(const std::vector<int>& input);
    void sortWithVector(const std::vector<int>& input);

    const std::deque<int>& getSortedDeque() const;
    const std::vector<int>& getSortedVector() const;
    long long getDequeSortTime() const;
    long long getVectorSortTime() const;

    static bool validateInput(const std::vector<std::string>& args);
    static bool isValidPositiveInteger(const std::string& arg);
    static std::vector<int> parseInput(const std::vector<std::string>& args);

  private:
    std::deque<int> deque_;
    std::vector<int> vector_;
    long long dequeSortTime_;
    long long vectorSortTime_;

    void fordJohnsonSort(std::deque<int>& container);
    void fordJohnsonSort(std::vector<int>& container);

    template <typename ContainerType>
    void mergeInsertSort(ContainerType& container);

    template <typename ContainerType>
    void sortTwoElements(ContainerType& container);

    template <typename ContainerType>
    std::tuple<PairVector<typename ContainerType::value_type>,
        typename ContainerType::value_type, bool>
    createSortedPairs(const ContainerType& container);

    template <typename ContainerType>
    ContainerType extractLargerElements(const PairVector<typename ContainerType::value_type>& pairs);

    template <typename ContainerType>
    ContainerType buildMainChain(const ContainerType& largerElements,
                      const PairVector<typename ContainerType::value_type>& pairs,
                      typename ContainerType::value_type leftover,
                      bool hasLeftover);

    template <typename ContainerType>
    void insertSmallerElements(ContainerType& mainChain,
                        const PairVector<typename ContainerType::value_type>& pairs);

    static std::vector<size_t> generateJacobsthalSequence(size_t pairCount);

    template <typename ContainerType>
    void insertLeftoverElement(ContainerType& mainChain, typename ContainerType::value_type leftover);

    template <typename ContainerType>
    static size_t binarySearch(const ContainerType& container, typename ContainerType::value_type value, size_t low, size_t high);

    template <typename ContainerType>
    void binaryInsert(ContainerType& container, typename ContainerType::value_type value, size_t end);
};

// Utility operator for printing pairs
template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

} // namespace FJASort
