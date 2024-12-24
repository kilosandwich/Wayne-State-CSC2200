//
// Lab_2:
// Maximum Subsequence Sum Problem
// Given (possibly negative) integers A1, A2, . . . , AN, find the maximum value
// 
// The given algorithm uses 3 loops --> O(N^3)
// 
// 1 - Verify the program run in your machine
// 2 - Implement and verify 2 more algorithms:
//     1-Two loops O(N^2)
//     2-One loop O(N)
// 
//  Capture enough runs to verify the execution time is matching the O(n^3), O(n^2) and O(n) per each algorithm
//  Will need to tweak the existing code to capture the running time in an array or equivlent
// 
// 3 - Create a report capturing the follwong items:
// 4 - Consider different values for N, and create random arrays VECTORS accordingly 
// 5 - Verify the run time of Cubic, Quadratic, and Linear
// 6 - Add snapshots graphs to verify your code execution by capturing the expected vs.actual algorithm output.
// 7 - Discuss Algorithm / function individual operations
// 8 - Uplaod your socurce and program report to CANVAS
// 


#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

/**
 * Cubic maximum subsequence sum algorithm. O(n)
 */
int maxSubSum_Cubic(const vector<int>& a)
{
    //start out the function at zero so it actually works.
    int maxSum = 0, thisSum = 0;

    //start at the beginning of the vector
    for (int i = 0; i < a.size(); ++i)
    {
        //look at all possible ending points 
        for (int j = i; j < a.size(); ++j)
        {

            thisSum = 0;
            //look at all possible subarrays between i and j
            for (int k = i; k <= j; ++k)
            {
                thisSum += a[k];
            }
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }
    return maxSum;
}


 /**
  * Quadratic maximum contiguous subsequence sum algorithm. O(n^2)
  */
int maxSubSum_Quadratic(const vector<int>& a)
{
    int maxSum = 0, thisSum = 0;

    for (int i = 0; i < a.size(); ++i)
    {
        thisSum = 0;
        //blindly sum every point beyond this point, whatever sum is the biggest is the one that gets kept
        for (int j = i; j < a.size(); ++j)
        {
            thisSum += a[j];
            if (thisSum > maxSum) {
                maxSum = thisSum;
            }
        }
 
    }

    return maxSum;
}

/**
 * Linear maximum subsequence sum algorithm. O(n)
 */

int maxSubSum_Linear(const vector<int>& a)
{
    int maxSum = 0, thisSum = 0, thisSum2 = 0;

    for (int j = 0; j < a.size(); ++j)
    {
        thisSum += a[j]; //begin summing
        thisSum2 += a[j];

        //blindly summing everything seems inefficient, surely there is a way to store a history of previous values to compare against to know
        // when to reset the sum (note, attempts to see previous values should be limited in order to not increase complexity of the program)
        //if the current sum is bigger than the maxSum encountered, replace the maximum sum
        if (thisSum > maxSum) {
            maxSum = thisSum; 
        }
        //resetting the sum to zero would mean that when the negatives of a sum outweigh its value, it assumes a new sum should occur
        //However, if this is the only sum that is counted, then this means that in the event of an ALL NEGATIVE array that the function will not work
        //it is very unlikely that an array will be all negative, so tbh this should be the only method to count, but it's good enough when tested. 
        //actually, come think of it, considering that both of the values are initialized at zero for MaxSum, doesn't that mean none of the functions
        //will work with an all negative array because they will never be replaced by a greater value?
        //Weird.
        if (thisSum2 < 0) {
            thisSum2 = 0;
        }
        if (thisSum2 > maxSum) {
            maxSum = thisSum2;
        }
 

    }

    return maxSum;
}


//this stuff came with the program and it works so who am I to doubt it. 
int main()
{
    int Max_random = 0;
    //Prove it works by just running it a bazillion times. We'll record the information somewhere
    for (int overandover = 0; overandover < 100; overandover++) {
        vector<signed int> a{ -2, 11, -4, 13, -5, -2 };  //(a1 through a3): 11 + -4 + 13 = 20.

        vector<signed int> arandom{};

        ++Max_random;//make the maximum size of the random array increase each time through the loop. 

        int maxSum = 0;
        int i;

        Max_random = (Max_random < 1000) ? Max_random : 1000;

        maxSum = maxSubSum_Cubic(a);
        cout << "Cubic maxSubSum: " << maxSum << endl;

        maxSum = maxSubSum_Quadratic(a);
        cout << "Qudaratic maxSubSum: " << maxSum << endl;

        maxSum = maxSubSum_Linear(a);
        cout << "Linear maxSubSum: " << maxSum << endl << endl;

        // seed the random # generator
        srand((unsigned)time(NULL));

        // fill the array vector with random numbers
        for (i = 0; i < Max_random; i++)
            arandom.push_back(rand() % 100 - 50);

        // print the elements to check randomness
        cout << "Random Array generated with " << arandom.size() << endl;;
        for (i = 0; i < arandom.size(); i++)
            cout << arandom[i] << " "; cout << endl << endl;


        // Cubic:
        auto start = chrono::high_resolution_clock::now();
        maxSum = maxSubSum_Cubic(arandom);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "Cubic maxSubSum: " << maxSum << endl;
        cout << "Time: maxSubSum_Cubic: = " << diff.count() << endl << endl;

        // Quadratic:
        start = chrono::high_resolution_clock::now();
        maxSum = maxSubSum_Quadratic(arandom);
        end = chrono::high_resolution_clock::now();
        diff = end - start;
        cout << "Qudaratic maxSubSum: " << maxSum << endl;
        cout << "Time: maxSubSum_Quadratic = " << diff.count() << endl << endl;

        // Linear:
        start = chrono::high_resolution_clock::now();
        maxSum = maxSubSum_Linear(arandom);
        end = chrono::high_resolution_clock::now();
        diff = end - start;
        cout << "Linear maxSubSum: " << maxSum << endl;
        cout << "Time: maxSubSum_Linear = " << diff.count() << endl << endl;


    }
    return 0;
}




