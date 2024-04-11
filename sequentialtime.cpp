#include <iostream>
#include <vector>
#include <ctime> // Header for timing
#include <cstdlib> // Header for random number generation

using namespace std;

// Function to partition the array and return the pivot index
int partition(vector<double>& arr, int low, int high) {
    double pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Function to perform quicksort
void quickSort(vector<double>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print the array
void printArray(const vector<double>& arr) {
    for (double num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    const int n = 5000; // Number of elements
    // Generate random elements for the array
    vector<double> arr(n);
    srand(time(0)); // Seed the random number generator with current time
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    cout << "Given array is: \n";
    printArray(arr);

    // Start timing
    clock_t start = clock();

    // Sort the array using quicksort
    quickSort(arr, 0, n - 1);

    // End timing
    clock_t end = clock();

    // Calculate time taken in milliseconds
    double time_taken_ms = (double(end - start) * 1000) / CLOCKS_PER_SEC;

    cout << "Sorted array is: \n";
    printArray(arr);

    cout << "Time taken: " << time_taken_ms << " ms" << endl;

    return 0;
}

