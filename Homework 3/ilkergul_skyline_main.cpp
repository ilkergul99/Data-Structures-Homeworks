#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "26352-ilkergul_skyline.h"

/**************************************
Date = 12/09/2020
Cs300 Third Assignment
Purpose = Implement a MPQ Class

**************************************/
using namespace std;

// I am using shell increment sequence
//Worst case it will take 0(N^2)
void shellsort( binalar * & towers, const int & size )
{
	int j;
	
	// Code was designed with respect to lecture notes
	for (int gap = size / 2; gap > 0; gap /= 2) {
		
		// I am using this loop to iterate over elements
		for (int i = gap; i < size; i++)
		{
			binalar temporary = towers[i];

			// Now I am using the advantage of the shell increment sequence
			for (j = i; j >= gap && temporary.x_coordinate < towers[j - gap].x_coordinate; j -= gap)
			{
				towers[j] = towers[j - gap];
			}
			// After finishing the loop iteration, I am assigning to the correct place in the array	
			towers[j] = temporary;
		}
	}
} 

void coordinatesort( binalar * & towers, const int & size )
{
	//The purpose is to order the elements with the same coordinates in an increasing order
	//Thus, I will have a completely increasing order and printing out the heights will be easier
	//It is a worthy extra computation in terms of using heap easier than only having shellsort
	for(int i = 1; i < size; i++)
	{
		for(int j = 1; j < size; j++)
		{
			if(towers[i].x_coordinate == towers[j].x_coordinate && towers[i].y_coordinate < towers[j].y_coordinate )
			{
				binalar temp = towers[i];
				towers[i] = towers[j];
				towers[j] = temp;

			}
		}
	}
}

//The purpose was to sort them in increasing order with respect to their x_coordinate
//If there are more than one elements that have same x coordinate then sort them with their status
//In this case right status will become before the left status
//However, in an edge case that I have prepared to check the smoothness of the code
//I found an error and to change the error, I need to get more computation 
//Hence, I decided not to use that case
//It was actually some sort of an insertion case
//Here, you can find the details
//To give an instance if following 5 indexex is having the same x coordinate with different status
//Order will look like: R, R, L, L, L

//void sidesort( binalar * & towers, const int & size )
//{
//	for(int i = 1; i < size; i++)
//	{
//		for(int j = 1; j < size; j++)
//		{
//			if(towers[i].x_coordinate == towers[j].x_coordinate && towers[i].status > towers[j].status )
//			{
//				binalar temp = towers[i];
//				towers[i] = towers[j];
//				towers[j] = temp;
//			}
//		}
//	}
//}


int main()
{
	string filename_buildings = "input.txt";			// Filename to use in ifstream operation
	ifstream input_towers;


	input_towers.open(filename_buildings);
	if(input_towers.is_open())
	{
		int arraysize, x_left, x_right, height;
		string line;
		getline(input_towers, line);
		istringstream first_line(line);
		first_line >> arraysize;
		binalar * manzara = new binalar[2*arraysize + 1];
		int index = 1;										//index of the array, we can use vector but in assignment it is stated as a array
		int label = 1;										//label of the array to perform O(1) operation in removing sequences
		while(!input_towers.eof())							//end of file check to prevent errors
		{
			getline(input_towers, line);
			istringstream others(line);
			others >> x_left >> height >> x_right;
			binalar left(x_left, height, label, 1);			//To add the coordinates to the array, 1 means left coordinate
			binalar right(x_right, height, label, 2);		//To add the coordinates to the array, 2 means right coordinate
			manzara[index] = left;
			manzara[index + 1] = right;
			label++;										//Now, I am changing the label for the next line of the file
			index += 2;										//Now, I am changing the index for the next line of the file

		}

		shellsort(manzara, 2*arraysize + 1);			//I am using shellsort to sort the x coordiantes in increasing order
		coordinatesort(manzara, 2*arraysize + 1);		//It helps me to sort the same x coordinate elements in a sense to smoothly operate in heap

		//sidesort(manzara, 2*arraysize + 1);			
		//It was an additional sorting for output, but I found a bug in an edge case
		//Therefore I am not using this sorting function

		MPQ BinaryHeap(2*arraysize + 1);	// I am creating the MPQ to use in checking heights to print out when needed
		
		int BinaryHeapHeight = 0;
		int outputheight = -1;

		// if the first elements' x coordinate is not equal to 0, then we can print 0 0 as the initial case
		if(manzara[1].x_coordinate != 0) 
		{
			//If first coordinate is not equal to zero then the start point is 0 0 we should print it
			cout << 0 << " " << 0 << endl;
			//outputheight = 0;
		}
		for(int i = 1; i< 2*arraysize + 1; i++)		//Now, I am getting in the loop to check the heights of the respected array elements to print the view
		{
			if(manzara[i].status == 1) // I am checking whether it is the left coordinate or right coordinate
			{

				BinaryHeap.insert(manzara[i].y_coordinate , manzara[i].label);
				if(BinaryHeapHeight != BinaryHeap.GetMax() &&  BinaryHeap.GetMax() > 0) // last part to prevent y coordiantes that are 0 or less
				//The height of a building can not be equal to 0, hence even though we don't get a such case we need to ensure safety
				{
					BinaryHeapHeight = BinaryHeap.GetMax();
					if(manzara[i].x_coordinate != manzara[i + 1].x_coordinate && outputheight != BinaryHeapHeight ) 
					// Since I ordered them to be in an increasing order, the output flow will not have a problem
					// then it is not max of that x coordinate so I do not need to print out because I am going to have 
					// another element that will have the highest height of that coordinate when its status is left
					{
						cout<< manzara[i].x_coordinate << " " << BinaryHeap.GetMax() <<endl;
						outputheight = BinaryHeap.GetMax();
						//we need to store the print height after each cout statement to compare in further cases
					}
				}	
			}
			else   // if the position of the element is right we will remove element to the heap
			{
				BinaryHeap.remove(manzara[i].label);			//to remove not exactly but implicitly since it a heap array
				if(BinaryHeapHeight != BinaryHeap.GetMax())		//If max height changed we should inspect it
				{
					BinaryHeapHeight = BinaryHeap.GetMax();
					if(i == 2*arraysize )							//if we are in the last element then we need to print height as 0
					{
						cout << manzara[i].x_coordinate << " " << 0 <<endl;
					}	
					else
					{
						if(manzara[i].x_coordinate != manzara[i + 1].x_coordinate && outputheight != BinaryHeapHeight) 
						//Since we order the coordinates in an increasing order if the next index x_coordinate is same 
						//then it is not max of that x coordinate so I do not need to print out because I am going to have 
						// another element that will have the highest height of that coordinate when its status is right
						{
							if(BinaryHeap.IsEmpty())
							{
								//If we have no elements left and the next x coordinate is 0
								//It means the building is finished so the height is 0
								cout << manzara[i].x_coordinate << " " << 0 <<endl;
								outputheight = 0;
							}
							else
							{
								//We got elements in the heap so we should print it
								cout << manzara[i].x_coordinate << " " << BinaryHeap.GetMax() <<endl;
								outputheight = BinaryHeap.GetMax(); 
							}
							 
						}
					}
				}	
			}
		}

		delete []manzara;			//dynamic memory allocation needs to be handled to prevent memory leak
	}

	return 0;
}