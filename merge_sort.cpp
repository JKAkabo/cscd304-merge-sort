//
// Created by John Kennedy on 2/23/20.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>

using namespace std;

void merge(int list[], int low, int mid, int high);
void merge_sort(int list[], int low, int high);
void print_array(int arr[], int size);
void generate_random_entries(int arr[], int size);
void merge_sort_and_plot();

int main() {
    int choice;

    cout << "1. Plot graph" << endl;
    cout << "2. Merge sort" << endl;

    while (true) {
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            merge_sort_and_plot();
            break;
        } else if (choice == 2) {
            int arr_size;
            cout << "How many entries do you want to make? ";
            cin >> arr_size;
            int arr[arr_size];
            generate_random_entries(arr, arr_size);
            cout << "Original Entries: ";
            print_array(arr, arr_size);
            merge_sort(arr, 0, arr_size - 1);
            cout << "Sorted Entries: ";
            print_array(arr, arr_size);
            break;
        } else {
            cout << "Invalid option!!" << endl;
        }
    }
}

void merge_sort_and_plot() {
    ofstream file_writer;
    file_writer.open("data.csv");
    for (int arr_size = 50; arr_size < 20000; arr_size+=50) {
        int arr[arr_size];
        generate_random_entries(arr, arr_size);

        chrono::steady_clock::time_point start = chrono::high_resolution_clock::now();
        merge_sort(arr, 0, arr_size - 1);
        chrono::steady_clock::time_point stop = chrono::high_resolution_clock::now();

        chrono::steady_clock::duration duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        file_writer << arr_size << "\t" << duration.count() << endl;
    }
    file_writer.close();
    cout << "Data is ready to be plotted" << endl;
}


void merge(int arr[], int left, int mid, int right) {
//    int i, j, k;
    int left_arr_size = mid - left + 1;
    int right_arr_size = right - mid;

    int left_arr[left_arr_size];
    int right_arr[right_arr_size];

    for (int i = 0; i < left_arr_size; ++i) {
        left_arr[i] = arr[left + i];
    }

    for (int j = 0; j < right_arr_size; ++j) {
        right_arr[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < left_arr_size && j < right_arr_size) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        }
        else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < left_arr_size) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < right_arr_size) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void print_array(int arr[], int size) {
    for (size_t i = 0; i < size; ++i) {
        if (i > 0) cout << ", ";
        cout << arr[i];
    }
    cout << endl;
}

void generate_random_entries(int arr[], int size) {
    srand((unsigned) time(nullptr));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 10000;
    }
}
