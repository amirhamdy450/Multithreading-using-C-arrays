#include <iostream>
#include <vector>
#include <thread>
#include <numeric>

// Function to calculate the sum of elements in a portion of the array
int calculateSum(const std::vector<int>& arr, size_t start, size_t end) {
    int sum = 0;
    for (size_t i = start; i < end; ++i) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    // Define the array and the number of threads
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const size_t numThreads = 2;

    // Calculate the size of each portion for the threads
    size_t chunkSize = numbers.size() / numThreads;

    // Vector to store thread objects
    std::vector<std::thread> threads;

    // Vector to store partial sums calculated by each thread
    std::vector<int> partialSums(numThreads, 0);

    // Launch threads
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back([i, chunkSize, &numbers, &partialSums]() {
            size_t start = i * chunkSize;
            size_t end = (i == numThreads - 1) ? numbers.size() : (i + 1) * chunkSize;
            partialSums[i] = calculateSum(numbers, start, end);
        });
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Calculate the final sum using the partial sums
    int finalSum = std::accumulate(partialSums.begin(), partialSums.end(), 0);

    // Display the result
    std::cout << "Sum of array elements: " << finalSum << std::endl;

    return 0;
}
