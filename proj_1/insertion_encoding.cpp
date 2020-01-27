// Author: Xiao 'Leo' Liu
// by only using stdio.

#include <iostream>
#include <string.h>
using namespace std;

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


int main(int argc, const char* argv[] ) {
	string x;
	while (getline(cin,x))
	{
		if (x.empty())
		{
			cout << endl;
			cout << endl; //I leave two space for one empty line
			              //read every two lines each time for decoding
		}
		else
		encoding_insertion(x);
	}
}