// Author: Xiao 'Leo' Liu
// by only using stdio.

#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

void merge_sort(string, int , int);
void merge(string, int, int, int);
void encoding_insertion(string);
void encoding_merge(string);




void encoding_insertion(string x)
{
	string origin;
	int i;
	int j;
	origin = x;
    string line[x.length()];
    line[0]=x;

    // cout << "This is the result of cyclic shifts." << endl;
    for (i=0; i< x.length(); i++)
    {
    	line[i]= x;
		// cout << line[i] << endl; // print out each cyclic shifts
		char temp; 
		temp= x.at(0);
		for (j=0; j< x.length()-1; j++)
		{
			x.at(j) = x.at(j+1);
		}
		x.at(j) = temp;
	}
	// done with cyclic shifts


	// start sorting lexcicographically
	string key_line;
	int key;

	// use Insertion sort
	for (j=1; j< x.length(); j++)
	{
		key = int(line[j].at(0));
		key_line = line[j];
		i = j-1;

		sort_by_fist_char:
		while( i>= 0 && int(line[i].at(0))>=int(key_line.at(0)) ) 
		{

			if (int(line[i].at(0))> int(key_line.at(0))) //when we need to compare/shift based on the 1st char
			{
				line[i+1] = line[i];
				i = i-1;
			}
			else // when we need to compare/shift but not based on the 1st char
			{
				for (int m=1; m<x.length(); m++) //check each char from 2nd to the end
				{
					if( i>= 0 && int(line[i].at(m))> int(key_line.at(m)) )
					{
						line[i+1] = line[i];
						i = i-1;
						goto sort_by_fist_char; // this part make sure we only check none-1st char 
						                        // when the 1st char of two strings are the same
					}
					else if ( i>= 0 && int(line[i].at(m)) < int(key_line.at(m)) )
					{
						goto outer_while;
					}
					else
					{
						//do nothing, keep the outer for-loop running
					}
				}
			}
		}
		outer_while:
		line[i+1]=key_line;	
	}

	// cout << "This is the result of Insertion sort." << endl;
	// for (j=0; j<x.length(); j++)
	// {
	// 	cout << line[j] << endl;
	// }

	for (j=0; j<x.length(); j++)
	{
		if ((origin.compare(line[j])) == 0)
		{
			int idx = j;
			// cout << "This index of the line." << endl;
			// cout << line[j] << endl;
			cout << j << endl;
		}
	}

	int count=1; // count = the occurance of each char
	for (j=0; j<x.length(); j++)
	{
		if ( j<x.length()-1 && int(line[j].at(x.length()-1)) == int(line[j+1].at(x.length()-1)) )
		{
			count++; //when there are multiple same char
		}
		else 
		{
			cout << count << " " << line[j].at(x.length()-1) << " "; //use the format of the output
			count = 1;
		}
	}
	cout << endl;
}

void merge(string line[], int l, int mid, int r)
{
    string new_line[line->size()];
    int i, j, k;
    i = l;
    k = l;
    j = mid+1;
    while(i<=mid && j<=r)
    {
        if (int(line[i].at(0)) < int(line[j].at(0)))
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
        else if (int(line[i].at(0)) == int(line[j].at(0)))
        {
            int m = 1;
            while (int(line[i].at(m)) == int(line[j].at(m)))
            {
                m++;
            }
            if (int(line[i].at(m)) < int(line[j].at(m)))
            {
                new_line[k] = line[i];
                k++;
                i++;
            }
            else
            {
                new_line[k] = line[j];
                k++;
                j++;
            }
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

void merge_sort(string line[], int l, int r) {
    int mid;
    if (l < r) {
        mid = floor((l + r) / 2);
        merge_sort(line, l, mid);
        merge_sort(line, mid + 1, r);
        merge( line, l, mid, r);
    }
}

void encoding_merge(string x) {
    string origin;
    int i;
    int j;
    origin = x;
    string line[x.length()];
    line[0] = x;
//    cout << "This is the result of cyclic shifts." << endl;
    for (i = 0; i < x.length(); i++) {
        line[i] = x;
//        cout << line[i] << endl; // print out each cyclic shifts
        char temp;
        temp = x.at(0);
        for (j = 0; j < x.length() - 1; j++) {
            x.at(j) = x.at(j + 1);
        }
        x.at(j) = temp;
    }
    // done with cyclic shifts
    int l;
    int r;
    l = 0;
    r = line->size()-1;

    // start sorting lexcicographically
    //use Merge sort
    merge_sort(line, l, r);

    // after finished merge sort, do the following
    for (j=0; j<x.length(); j++)
    {
        if ((origin.compare(line[j])) == 0)
        {
            int idx = j;
            // cout << "This index of the line." << endl;
            // cout << line[j] << endl;
            cout << j << endl;
        }
    }

    int count=1; // count = the occurance of each char
    for (j=0; j<x.length(); j++)
    {
        if ( j<x.length()-1 && int(line[j].at(x.length()-1)) == int(line[j+1].at(x.length()-1)) )
        {
            count++; //when there are multiple same char
        }
        else
        {
            cout << count << " " << line[j].at(x.length()-1) << " "; //use the format of the output
            count = 1;
        }
    }
    cout << "\n";
}


int main(int argc, const char* argv[] ) {
	string x;
    string method(argv[1]);
    if (method == "insertion") {
        while (getline(cin, x)) {
            if (x.empty()) {
                cout << 0 <<endl; //I leave one space for one empty line
                cout <<endl;
            } else
                encoding_insertion(x);
        }
    }
    else if (method == "merge")
    {
        while (getline(cin, x)) {
            if (x.empty()) {
                cout << 0 << endl; //I leave one space for one empty line
                cout << endl;
            } else
                encoding_merge(x);
        }
    }
    else
        return 0;
}