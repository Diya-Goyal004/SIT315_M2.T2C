#include <iostream>
#include <vector>

using namespace std;

// Function to partition the array and return the pivot index
// This function takes a vector of doubles (arr), a low index, and a high index.
// It selects the last element (arr[high]) as the pivot element.
// It rearranges the array so that elements smaller than the pivot come before it,
// and elements greater than the pivot come after it.
// It returns the index of the pivot element after rearrangement.
int partition(vector<double>& arr, int low, int high) {
    double pivot = arr[high]; // Select the pivot element
    int i = low - 1; // Initialize the index of the smaller element

    // Iterate through the array from low to high-1
    for (int j = low; j < high; j++) {
        // If the current element is smaller than or equal to the pivot
        if (arr[j] < pivot) {
            i++; // Increment index of the smaller element
            swap(arr[i], arr[j]); // Swap arr[i] and arr[j]
        }
    }
    swap(arr[i + 1], arr[high]); // Swap arr[i+1] and arr[high] (pivot)
    return i + 1; // Return the partitioning index
}

// Function to perform quicksort
// This function recursively sorts the elements of the array using the quicksort algorithm.
// It takes a vector of doubles (arr), a low index, and a high index.
void quickSort(vector<double>& arr, int low, int high) {
    if (low < high) {
        // pi is the partitioning index, arr[pi] is now at the correct position
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after the partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print the array
// This function takes a const reference to a vector of doubles (arr) and prints its elements.
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

    vector<double> arr(n); // Create a vector of doubles of size n to store elements

    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; // Input each element into the vector
    }

    cout << "Given array is: \n";
    printArray(arr); // Print the original array

    quickSort(arr, 0, n - 1); // Sort the array using quicksort

    cout << "Sorted array is: \n";
    printArray(arr); // Print the sorted array

    return 0; // Exit the program
}
