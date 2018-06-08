// MultiMerge.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <pthread.h>
#include <time.h>
#include<stdlib.h>
#include<stdio.h>

// number of elements in array
#define MAX 100

// number of threads
#define THREAD_MAX 4

using namespace std;
int b[MAX];
int a[MAX];
int part = 0;
void NotMultiMergeSort(int arr[], int l, int r);

void merge(int low, int mid, int high)
{
	int* left = new int[mid - low + 1];
	int* right = new int[high - mid];
	int n1 = mid - low + 1, n2 = high - mid, i, j;

	for (i = 0; i < n1; i++)
		left[i] = a[i + low];

	for (i = 0; i < n2; i++)
		right[i] = a[i + mid + 1];

	int k = low;
	i = j = 0;
	while (i < n1 && j < n2) {
		if (left[i] <= right[j])
			a[k++] = left[i++];
		else
			a[k++] = right[j++];
	}

	while (i < n1) {
		a[k++] = left[i++];
	}

	while (j < n2) {
		a[k++] = right[j++];
	}
}

void merge_sort(int low, int high)
{
	int mid = low + (high - low) / 2;
	if (low < high) {
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
}
void* merge_sort(void* arg)
{
	// which part out of 4 parts
	int thread_part = part++;

	// calculating low and high
	int low = thread_part * (MAX / 4);
	int high = (thread_part + 1) * (MAX / 4) - 1;

	// evaluating mid point
	int mid = low + (high - low) / 2;
	if (low < high) {
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
	return 0;
}

int main()
{
	for (int i = 0; i < MAX; i++)
	{
		b[i] = rand() % 500;
		a[i] = b[i];
	}

	// t1 and t2 for calculating time for merge sort
	clock_t t1, t2;


	pthread_t threads[THREAD_MAX];
	t1 = clock();
	// creating 4 threads
	for (int i = 0; i < THREAD_MAX; i++)
		pthread_create(&threads[i], NULL, merge_sort,
		(void*)NULL);

	// joining all 4 threads
	for (int i = 0; i < 4; i++)
		pthread_join(threads[i], NULL);
	
	// merging the final 4 parts
	merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);
	merge(MAX / 2, MAX / 2 + (MAX - 1 - MAX / 2) / 2, MAX - 1);
	merge(0, (MAX - 1) / 2, MAX - 1);

	t2 = clock();
	cout << "Sorted array: ";
	for (int i = 0; i < MAX; i++)
		cout << a[i] << " ";

	cout <<endl<< "Time taken:" << (t2 - t1) /(double)CLOCKS_PER_SEC << endl;
	clock_t t3;
	NotMultiMergeSort(b, 0, MAX - 1);
	t3 = clock();
	cout << "Sorted array: ";
	for (int i = 0; i < MAX; i++)
		cout << b[i] << " ";
	cout << endl << "Time taken: " << (t3 - t2) /(double)CLOCKS_PER_SEC << endl;
	system("pause");
	return 0;
}


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void NotMultiMerge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int *L = new int[n1];
	int *R=new int [n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void NotMultiMergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		NotMultiMergeSort(arr, l, m);
		NotMultiMergeSort(arr, m + 1, r);

		NotMultiMerge(arr, l, m, r);
	}
}