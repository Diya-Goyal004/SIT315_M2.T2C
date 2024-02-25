#include <iostream>
#include <vector>
#include <pthread.h> // Include pthread library for threading

using namespace std;

// Struct to pass arguments to the sorting function
struct SortArgs {
    vector<double> *arr; // Pointer to the array to be sorted
    int low; // Index of the low element
    int high; // Index of the high element
};

// Function to partition the array and return the pivot index
int partition(vector<double>& arr, int low, int high) {
    double pivot = arr[high]; // Choose the pivot as the last element
    int i = low - 1; // Initialize index of smaller element

    // Iterate through the array
    for (int j = low; j < high; j++) {
        // If the current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // Increment index of smaller element
            swap(arr[i], arr[j]); // Swap arr[i] and arr[j]
        }
    }
    swap(arr[i + 1], arr[high]); // Swap arr[i+1] and arr[high] (pivot)
    return i + 1; // Return the partitioning index
}

// Function to perform quicksort
void* quickSortHelper(void* arg) {
    SortArgs* args = (SortArgs*)arg; // Cast void pointer to SortArgs pointer
    vector<double>& arr = *(args->arr); // Dereference and get the array
    int low = args->low; // Get the low index
    int high = args->high; // Get the high index

    if (low < high) {
        int pi = partition(arr, low, high); // Get partitioning index

        // Create arguments for left and right partitions
        SortArgs leftArgs = {&arr, low, pi - 1};
        SortArgs rightArgs = {&arr, pi + 1, high};

        // Create pthreads for left and right partitions
        pthread_t leftThread, rightThread;
        pthread_create(&leftThread, NULL, quickSortHelper, (void*)&leftArgs);
        pthread_create(&rightThread, NULL, quickSortHelper, (void*)&rightArgs);

        // Join the pthreads to wait for their completion
        pthread_join(leftThread, NULL);
        pthread_join(rightThread, NULL);
    }

    pthread_exit(NULL); // Exit the thread
}

// Function to print the array
void printArray(const vector<double>& arr) {
    for (double num : arr) {
        cout << num << " "; // Print each element followed by a space
    }
    cout << endl; // Print a newline character after printing all elements
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<double> arr(n); // Create a vector to store elements
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; // Input each element into the vector
    }

    cout << "Given array is: \n";
    printArray(arr); // Print the original array

    // Create arguments for the initial call to quickSortHelper
    SortArgs args = {&arr, 0, n - 1};

    // Create a pthread for the initial call to quickSortHelper
    pthread_t thread;
    pthread_create(&thread, NULL, quickSortHelper, (void*)&args);

    // Join the pthread to wait for its completion
    pthread_join(thread, NULL);

    cout << "Sorted array is: \n";
    printArray(arr); // Print the sorted array

    return 0;
}
