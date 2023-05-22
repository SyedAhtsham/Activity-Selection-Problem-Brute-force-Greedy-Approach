//
//  main.cpp
//  Activity Selection Problem
//
//  Created by Syed Ahtsham on 12/25/20.
//  Copyright © 2020 Syed Ahtsham. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <string.h>
#include <climits>
#include <stdlib.h>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>
#include <time.h>

using namespace std::chrono;
using namespace std;



//structure for storing the starting and finishing time for an activity
struct Activity
{
    int start;
    int finish;

};


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(Activity arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    Activity L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i].finish <= R[j].finish) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(Activity arr[],int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m = (l+r-1)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

//Greedy Approach Algorithm for Activity Selection problem
int maxActivitiesGreedyApproach(Activity arr[], int n)
{
    int i, j, counter = 0;
  
    mergeSort(arr, 0, n);
    i = 0;
    for (j = 1; j < n; j++)
    {
   
      if (arr[j].start >= arr[i].finish)
      {
          counter++;
          i = j;
      }
    }
    return counter+1;
}

int maxActivitiesBruteForce(int start[], int finish[], int n) {
  int index, j, counter = 1;
  vector < int > finalActivities;
    vector < int > tempActivities;

  // Array that will help us find all combinations possible of the activities
  int combinations[n];
  for (int i = 0; i < n; i++)
    combinations[i] = i;

  // find value for all combinations
  do {
    index = 0; //starting activity always 0

      j=1;
    while (j<n) {
      if (start[combinations[j]] >= finish[combinations[index]]) {
        tempActivities.push_back(combinations[j]);
        index = j;
      }
        j++;
    }
      //if statement to check if the size of the temp vector is greater than final vector
    if (tempActivities.size() > finalActivities.size())
      finalActivities = tempActivities;

    tempActivities.erase(tempActivities.begin(), tempActivities.end());

  } while (std::next_permutation(combinations, combinations + n));

  //printing the sequence with max tasks
  for (int i = 0; i < finalActivities.size(); i++)
      counter++;
    
    return counter+1;
}




int main() {
  
    //an integer array for storing the sizes of different arrays of activities
    int size[6] = {5, 10, 15, 20, 25, 30};

    int j=0;
    
    
    //while loop for executing the functions for different sizes of number of activities
    while(j<6){
        
        //activity type array is declared of size
    Activity act_arr[size[j]];

        
   srand(time(0));

        //loop to generate the random starting and finishing time for activities
    int i=0, tempStart, tempFinish;
       while(i<size[j])
       {
           tempStart = rand() % 100;
           tempFinish = rand() % 100;

           if(tempStart<tempFinish){

               act_arr[i].start = tempStart;
               act_arr[i].finish = tempFinish;
               i++;
           }

       }

        //for loop to store the starting and finishing time for activities into two arrays
    int starting[size[j]], finishing[size[j]];
    for(int i=0; i<size[j]; i++)
    {
        starting[i] = act_arr[i].start;
        finishing[i] = act_arr[i].finish;

    }

// Functions are called for different set of activites and execution time is noted
        cout<<"--> Greedy Approach"<<endl;
    steady_clock::time_point t1 = steady_clock::now();
    cout<<"Maximum number of Activities: "<<maxActivitiesGreedyApproach(act_arr, size[j]);
    steady_clock::time_point t2 = steady_clock::now();

      duration<double, milli> time_span = duration_cast<duration<double, milli>>(t2 - t1);

  cout << "\nTime taken: " << time_span.count() << " ms" << endl;

        cout<<endl;
        cout<<endl;
        
        // Functions are called for different set of activites and execution time is noted
        cout<<"--> Brute Force Approach"<<endl;
         steady_clock::time_point t3 = steady_clock::now();
          cout<<"Maximum number of Activities: "<<maxActivitiesBruteForce(starting,finishing, size[j]);
          steady_clock::time_point t4 = steady_clock::now();

            duration<double, milli> time_span2 = duration_cast<duration<double, milli>>(t4 - t3);

        cout << "\nTime taken: " << time_span2.count() << " ms" << endl;

              cout<<endl;
        
        j++;
    }

           cout<<endl;
           cout<<endl;
    cout<<endl;
    return 0;
}
