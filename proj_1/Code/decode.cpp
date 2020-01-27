// Author: Xiao 'Leo' Liu
// by only using stdio.

#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;


void merge(string line[], int l, int mid, int r,int sum)
{
    string new_line[sum];
    int i, j, k;
    i = l;
    k = l;
    j = mid+1;
    while(i<=mid && j<=r)
    {
        if (int(line[i].at(0)) <=int(line[j].at(0)))
        {
            new_line[k] = line[i];
            k++;
            i++;
        }
        else if (int(line[i].at(0)) > int(line[j].at(0)))
        {
            new_line[k] = line[j];
            k++;
            j++;
        }
    }
    while (i<=mid)
    {
        new_line[k] = line[i];
        k++;
        i++;
    }
    while (j<= r)
    {
        new_line[k] = line[j];
        k++;
        j++;
    }
    for (i = l; i<k ; i++)
    {
        line[i] = new_line[i];
    }
}

void merge_sort(string line[], int l, int r,int sum) {
    int mid;
    if (l < r) {
        mid = floor((l + r) / 2);
        merge_sort(line, l, mid,sum);
        merge_sort(line, mid + 1, r,sum);
        merge( line, l, mid, r,sum);
    }
}



void decode_merge (string x, string y)
{
    int i;
    int j;
    int idx = 0;
    for(i=0;i<x.length();i++)
    {
        idx = idx * 10 + x.at(i) - '0';
    }

    string last[y.length()];
    int arr[y.length()] = {0};
    int count;
    j = 0;

    for (i=0; i<y.length()-1; i++) // divide char and count
    {
        count = 0;
        while (y.at(i) >= '0' && y.at(i) <= '9')
        {
            count = count * 10 + y.at(i) - '0';
            i = i+1;
        }
        arr[j]=count;
        i= i+1;
        last[j] = y.at(i);
        j = j+1;
        i = i+1;
    }

    int sum=0;
    for (int n=0; n<j; n++){ //compute the num of char
        sum = sum+arr[n];
    }
    string true_last[sum];
    string origin_last[sum];
    string add_last[sum];
    int m=0;
    for (int n=0; n<j; n++){
        for (i=0; i< arr[n];i++)
        {
            true_last[m] = last[n];
            origin_last[m] = last[n];// save the last[]
            add_last[m]=last[n];
            m++;
        }
    }

    int l = 0;
    int r = sum-1;
    merge_sort(true_last, l, r,sum);// get the first[]
    int next[sum] = {0};
    for (i=0; i<sum; i++) // get the next[]
    {
        j=0;
        while(true_last[i]!=origin_last[j])
        {
            j++;
        }
        next[i]=j;
        origin_last[j]="NULL";
    }

    int start_index; // This the the core part of decoding
    start_index = next[idx];
    for (i=0; i<sum; i++)
    {
        cout<< add_last[start_index];
        start_index = next[start_index];
    }
    cout << endl; // finish one line of decoding
}

void decode_insertion(string x, string y)
{
    int i;
    int j;
    int idx = 0;
    for(i=0;i<x.length();i++)
    {
        idx = idx * 10 + x.at(i) - '0';
    }

    string last[y.length()];
    int arr[y.length()] = {0};
    int count;
    j = 0;

    for (i=0; i<y.length()-1; i++) // divide char and count
    {
        count = 0;
        while (y.at(i) >= '0' && y.at(i) <= '9')
        {
            count = count * 10 + y.at(i) - '0';
            i = i+1;
        }
        arr[j]=count;
        i= i+1;
        last[j] = y.at(i);
        j = j+1;
        i = i+1;
    }
    int sum=0;
    for (int n=0; n<j; n++){ //compute the num of char
        sum = sum+arr[n];
    }
    string true_last[sum];
    string origin_last[sum];
    string add_last[sum];
    int m=0;
    for (int n=0; n<j; n++){
        for (i=0; i< arr[n];i++)
        {
            true_last[m] = last[n];
            origin_last[m] = last[n];// save the last[]
            add_last[m]=last[n];
            m++;
        }
    }

    string key; // insertion sort in decoding
    for (j=1; j<sum; j++)
    {
        key = true_last[j];
        i = j-1;
        while(i>=0 && true_last[i]>key)
        {
            true_last[i+1] = true_last[i];
            i = i-1;
        }
        true_last[i+1]=key;
    }

    int next[sum] = {0};
    for (i=0; i<sum; i++) // get the next[]
    {
        j=0;
        while(true_last[i]!=origin_last[j])
        {
            j++;
        }
        next[i]=j;
        origin_last[j]="NULL";
    }

    int start_index; // This the the core part of decoding
    start_index = next[idx];
    for (i=0; i<sum; i++)
    {
        cout<< add_last[start_index];
        start_index = next[start_index];
    }
    cout << endl; // finish one line of decoding
}


int main(int argc, const char* argv[] ) {
    string x;
    string y;
    string y1;
    string method(argv[1]);
    if (method == "insertion") {
        while (getline(cin, x)) {
            getline(cin, y);
            if (y.empty()) {
                cout <<endl;
            } else
                decode_insertion(x,y);
        }
    }
    else if (method == "merge")
    {
        while (getline(cin, x)) {
            getline(cin, y);
            if (y.empty()) {
                cout << endl;
            } else
                decode_merge(x,y);
        }
    }
    else
        return 0;
}