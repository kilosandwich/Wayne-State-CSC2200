//
//
// Lab_9:
//
// Use the startup code as a reference, and the predefined array of integers for testing each sorting algorithm.
// Implement three sorting algorithms:
//  
// 1-Selection Sort 
// 2-Shell Sort
// 3-Insertion Sort
//  
// Include a brief summary of your testing and any observations made during the implementation.
//

//
// Some algorithms are provided for reference:
// Original vector : 7 19 10 2 5 13 11 4 6 8 17 9 20 12 15 3 1 14 16 18
// Sorted vectors :
// Bubble Sort      : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// Selection Sort   : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// Insertion Sort   : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// Shell Sort       : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// Heap Sort        : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// Merge Sort       : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// Quick Sort       : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// Count Sort       : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// Radix Sort       : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// Radix Sort       : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
//


#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;
//Step 1, read through existing code so I can understand it
//because I am not using some of the already existing functions
//all that I have to do is determine how to use some functions.

//Step 2 determine the to do list:
//Selection Sort
//Shell Sort
//Insertion sort
//yay they work, I followed the slides correctly woooooh


//Thanks for these functions I uess, I don't really trust them but they're nice to have
void customCopy(const vector<int>& source, vector<int>& destination) {
    // Resize the destination vector to match the size of the source vector
    destination.resize(source.size());

    copy(source.begin(), source.end(), destination.begin());
}

//this swaps ints 
void customSwap(int& a, int& b) {
    // Swap  a and b
    int temp = a;
    a = b;
    b = temp;
}
//This function prints out whatever vector you slide in.
//Wait I'm supposed to use Vectors, ug I dislike vectors
void printVector(const vector<int>& vec) {
    //for every single int within the inputted vector, print it out
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

// Bubble Sort algorithm
void bubbleSort(vector<int>& vec) {
    cout << "Bubble Sort\t: ";

    // Iterate through the vector multiple times, swapping adjacent elements if they are in the wrong order
    for (int i = 0; i < static_cast<int>(vec.size()) - 1; i++) {
        for (int j = 0; j < static_cast<int>(vec.size()) - i - 1; j++) {
            // Swap if the current element is greater than the next one
            if (vec[j] > vec[j + 1]) {
                customSwap(vec[j], vec[j + 1]);
            }
        }
    }

    printVector(vec);
}

//These are the sorting algorithm that I need to get working
//the functions do not need to return anything (yay!)
//however, they do need to take vectors as inputs and 
//sort the array after it is done


// Selection Sort algorithm
void selectionSort(vector<int>& vec) {
    //selection sort involves taking the vector
    //and turning it into two parts
    //the ever growing organized part, and the ever shrinking
    //unorganized part. 
    //the minimum of the unorganized part is located, and swapped into the 
    //organized part
    //because the minimum of the unoranized part will always be the
    //next greatest compared to the previous number in the organized part
    //the list will become ordered from least to greatest.
    //SCIENCE!!

    int length = vec.size(); //find the length of the vector
    //time to iterate through the vector, and shove the minimum one into the end
    for (int i = 0; i < length; i++) {
        //find the minimum element of the unsorted index
        int indexofminimum = i; //this is the assumed to be minimum member
        for (int j = i + 1; j < length; j++) {
            //find the minimum in the unorganized section
            if (vec[j] < vec[indexofminimum]) {
                //found a smaller number? That's the new minimum
                indexofminimum = j;
            }
        }
        //put that organized minimum into its place. WOW
        swap(vec[i], vec[indexofminimum]);

    }



    cout << "\nSelection Sort*\t:";
    //wow I doubled creating it for absolutely no reason at all woooh
    printVector(vec);
}

// Insertion Sort algorithm
void insertionSort(vector<int>& vec) {
    //insertion sort involves splitting the list into two parts
    //the organized part and the unorganized part
    //the next number from the unorganized part is taken, then
    //compared to all previous numbers in the organized part to be put 
    //into order
    int length = vec.size(); // find the length, we have to iterate through
    //this after all

    //we start at one, because there's nothing to compare to yet if we don't
    for (int i = 1;i < length; i++) {
        int findnumbersgreaterthanthistoright = vec[i]; //lengthy variable describing what it does
        
        //shift all elements that are greater to the right of it.
        //ONLY consider elements in the sorted section
        int j;
        for (j = i - 1; j >= 0 && vec[j] > findnumbersgreaterthanthistoright ; j--) {
            //for the remaining elements in the unsorted section that are not i, move them
            //to the right
            vec[j + 1] = vec[j];
        }
        vec[j + 1] = findnumbersgreaterthanthistoright;
        //put the element that we were sorting in comparison to

    }

    cout << "\nInsertion Sort*\t:";

    printVector(vec);
}

// Shell Sort algorithm
void shellSort(vector<int>& vec) {
    //shell sort involves compariing numbers starting at the
    //furthest gap of the array, then narrowing the gap
    //to be blunt, this one was tricky, I am very confused
    //about how this works, but I just know that it works
    //this is why bubble sort is my friend.

    int length = vec.size();

    for (int gap = length / 2; gap > 0; gap /= 2) {
        //it feels weird using i in an inner loop.
        for (int i = gap; i < length; i++) {
            int temp = vec[i];
            int j;
            //insertion sort time
            for (j = i; j >= gap && vec[j - gap] > temp; j -= gap) {
                vec[j] = vec[j - gap];
            }
            vec[j] = temp;
        }
    }





    cout << "\nShell Sort*\t:";

    printVector(vec);
}






//ignore these you don't need them















// Heapify function for Heap Sort
void heapify(vector<int>& vec, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Find the largest element among the root, left child, and right child
    if (left < n && vec[left] > vec[largest]) {
        largest = left;
    }

    if (right < n && vec[right] > vec[largest]) {
        largest = right;
    }

    // If the largest element is not the root, swap the root with the largest element and heapify the affected subtree
    if (largest != i) {
        customSwap(vec[i], vec[largest]);
        heapify(vec, n, largest);
    }
}

// Heap Sort algorithm
void heapSort(vector<int>& vec) {
    cout << "\nHeap Sort\t: ";
    int n = static_cast<int>(vec.size());

    // Build a max heap by repeatedly heapifying the vector
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vec, n, i);
    }

    // Extract elements from the heap one by one and heapify the remaining heap
    for (int i = n - 1; i > 0; i--) {
        customSwap(vec[0], vec[i]);
        heapify(vec, i, 0);
    }


    printVector(vec);
}

// Merge function for Merge Sort
void merge(vector<int>& vec, int l, int m, int r) {
    // Function to merge two subarrays of vec[]
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary vectors L and R
    vector<int> L(n1), R(n2);

    // Copy data to temporary vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = vec[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = vec[m + 1 + j];

    // Merge the temporary vectors back into vec[l..r]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        }
        else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort algorithm
void mergeSort(vector<int>& vec, int l, int r) {
    // Recursive function to perform merge sort on vec[l..r]
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Recursively sort the first and second halves
        mergeSort(vec, l, m);
        mergeSort(vec, m + 1, r);

        // Merge the sorted halves
        merge(vec, l, m, r);
    }
}

// Partition function for Quick Sort
int partition(vector<int>& vec, int low, int high) {
    // Function to rearrange elements around the pivot
    int pivot = vec[high];
    int i = (low - 1);

    // Traverse the array and rearrange elements
    for (int j = low; j <= high - 1; j++) {
        if (vec[j] < pivot) {
            i++;
            customSwap(vec[i], vec[j]);
        }
    }

    // Swap the pivot element with the element at (i + 1)
    customSwap(vec[i + 1], vec[high]);
    return (i + 1);
}

// Quick Sort algorithm
void quickSort(vector<int>& vec, int low, int high) {
    // Recursive function to perform quick sort on vec[low..high]
    if (low < high) {
        // pi is the partitioning index
        int pi = partition(vec, low, high);

        // Recursively sort the elements before and after partition
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

// Count Sort algorithm
void countSort(vector<int>& vec) {
    cout << "\nCount Sort\t: ";
    // Find the maximum element in the vector
    int max = *max_element(vec.begin(), vec.end()) + 1;

    // Create a count vector to store the count of each element
    vector<int> count(max, 0);

    // Count the occurrences of each element in the vector
    for (int num : vec) {
        count[num]++;
    }

    // Reconstruct the sorted vector based on the count array
    size_t index = 0;
    for (int i = 0; i < max; i++) {
        while (count[i] > 0) {
            vec[index++] = i;
            count[i]--;
        }
    }

    printVector(vec);
}

// Counting Sort algorithm for Radix Sort
void countingSort(vector<int>& vec, int exp) {
    const int radix = 10;
    // Function to perform counting sort based on the digit at the current radix place
    vector<int> output(vec.size());
    vector<int> count(radix, 0);

    // Count occurrences of digits at the current radix place
    for (int i = 0; i < static_cast<int>(vec.size()); i++)
        count[(vec[i] / exp) % radix]++;

    // Cumulative sum to get the correct position of each digit
    for (int i = 1; i < radix; i++) // Fix: Change 'radix' to '< radix'
        count[i] += count[i - 1];

    // Build the output array using the count array
    for (int i = static_cast<int>(vec.size()) - 1; i >= 0; i--) {
        output[count[(vec[i] / exp) % radix] - 1] = vec[i];
        count[(vec[i] / exp) % radix]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < static_cast<int>(vec.size()); i++) {
        vec[i] = output[i];
    }
}

// Radix Sort algorithm
void radixSort(vector<int>& vec) {
    // Function to perform radix sort on the vector
    int max = *max_element(vec.begin(), vec.end());

    // Perform counting sort for every digit place (units, tens, hundreds, etc.)
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(vec, exp);

    cout << "\nRadix Sort\t: ";
    printVector(vec);
}













// Main function
int main() {
    // Example vector with 20 elements
    vector<int> vec = { 7, 19, 10, 2, 5, 13, 11, 4, 6, 8, 17, 9, 20, 12, 15, 3, 1, 14, 16, 18 };

    cout << "\nOriginal vector\t: ";
    printVector(vec);
    cout << "\nSorted vectors:\n";

    // Bubble Sort
    vector<int> bubbleVec(vec);
    bubbleSort(bubbleVec);

    // Selection Sort
    vector<int> selectionVec(vec);
    selectionSort(selectionVec);
    cout << "\nSelection Sort\t: ";
    printVector(selectionVec);
    // Insertion Sort
    vector<int> insertionVec(vec);
    insertionSort(insertionVec);
    cout << "\nInsertion Sort\t: ";
    printVector(insertionVec);

    // Shell Sort
    vector<int> shellVec(vec);
    shellSort(shellVec);
    cout << "\nsShell Sort\t: ";
    printVector(shellVec);

    // Heap Sort
    vector<int> heapVec(vec);
    heapSort(heapVec);

    // Merge Sort
    vector<int> mergeVec(vec);
    mergeSort(mergeVec, 0, mergeVec.size() - 1);
    cout << "\nMerge Sort\t: ";
    printVector(mergeVec);

    // Quick Sort
    vector<int> quickVec(vec);
    quickSort(quickVec, 0, quickVec.size() - 1);
    cout << "\nQuick Sort\t: ";
    printVector(quickVec);

    // Count Sort
    vector<int> countVec(vec);
    countSort(countVec);

    // Radix Sort
    vector<int> radixVec(vec);
    radixSort(radixVec);
    cout << "\nRadix Sort\t: ";
    printVector(radixVec);

    return 0;
}
