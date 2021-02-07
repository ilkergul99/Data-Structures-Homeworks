#ifndef ilkergul_Skyline_H
#define ilkergul_Skyline_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct binalar					//This is to store x coordinate, y coordiante, label, and status
{
	int x_coordinate;
	int y_coordinate;
	int label;
	int status;

	binalar()					//Default constructor
	{
		x_coordinate = -1;
		y_coordinate = -1;
		label = -1;
		status = 0;
	}
	binalar(const int & x, const int & y, const int & lab, const int & position)		//constructor with parameters
	{
		x_coordinate = x;
		y_coordinate = y;
		label = lab;
		status = position;
	}

	//This is for preventing any bad cases, since I may need to use it in main function
	//If one wants to compare the elements without specfying its element
	//I want to guarantee to prevent and errors
	//But, I have not used it
	//Because comparing heights is enough to find the answers
	bool operator > (const binalar & comparison) const			
	{
		return ((*this).x_coordinate > comparison.x_coordinate);
	}
	bool operator < (const binalar & comparison) const
	{
		return ((*this).x_coordinate < comparison.x_coordinate);
	}

};

//Since, I have a specific design with coordinates in which I will use integers
//I did not need to specify a template class
//However, if it was asked to use for general cases and input is unclear
//Then, converting to a template class will only need some changes in changing the class height
//and some modifications on remove and getmax functions

class MPQ
{
private:
	struct heapnode
	{
		int height;
		int label;

		heapnode()	//default constructor
		{
			label = 0;
		}
		heapnode(const int & y, const int & Label)		//constructor with parameter
		{
			height = y;
			label = Label;
		}

		//This is for preventing any bad cases, since I am using structs one element for comparison
		//I did not use it but if I wanted to use it helps me to get rid of errors
		//If one wants to compare the elements without specfying its element
		//I want to guarantee to prevent unwanted errors
		//Again it is only implemented for compactness
		bool operator > (const heapnode & comparison) const
		{
			return ((*this).height > comparison.height);
		}
		bool operator < (const heapnode & comparison) const
		{
			return ((*this).height < comparison.height);
		}
	};
	int currentHeapsize;
	//This to check how many elements we have in the heap

	heapnode * HeapArray;	
	//Heap array pointer initializer
	// I have decided to use dynamic memory 

	int * Location;			
	//Private array of integers
	// It was specified as to keep an private integer array in the guideline


protected:
	//The crucial part of the class to maintain heap order structure 
	// When the heap order changed due to remove, we need to fix it
	void percolateDown(int hole)
	{
		int child;
		heapnode temp = HeapArray[hole];
		//Structure of the function designed with respect to the lecture notes

		for(; hole*2 <= currentHeapsize; hole = child)
		{
			child = 2*hole;
			if(child!= currentHeapsize && HeapArray[child + 1] > HeapArray[child])
			{
				child++;
			}
			if(HeapArray[child] > temp)
			{
				//If there is a change to be done
				//I need to change the places in the private dynamic array
				//To prevent further errors in finding the location with respect to label
				HeapArray[hole] = HeapArray[child];
				Location[HeapArray[hole].label] = hole; 
			}
			else
			{
				break;
			}
		}
		//Aforementioned case was done here too
		//It is crucial to maintain this property for removing purposes when needed
		HeapArray[hole] = temp;
		Location[temp.label] = hole;
	}

public:
	MPQ()											//Constructor
	{
		currentHeapsize = 0;
	}
	MPQ(const int & size)							//constructor with parameters
	{
		currentHeapsize = 0;						//If I add something I will modify it
		HeapArray = new heapnode[size];				//I have assigned the size of the array
		Location = new int[size];					//I have assigned the size of the array
	}
	~MPQ()											//Destructor
	{
		delete []HeapArray;			//since I dynamically allocated memory, I need to delete in destructor
		delete []Location;			//since I dynamically allocated memory, I need to prevent memory leaks
	}

	void insert(const int & value, const int & label)
	{
		heapnode GonnabeAdded(value, label);
		int hole = ++currentHeapsize;
		// I am doing the percolate operation to keep the heap order structure
		for(; hole > 1 && value > HeapArray[hole/2].height; hole /=2)
		{
			HeapArray[hole] = HeapArray[hole/2];
			Location[HeapArray[hole].label] = hole;
		}
		//Next statements to remove them in constant time
		//The purpose is to actually directly locate them when parameter is given
		HeapArray[hole] = GonnabeAdded;
		Location[GonnabeAdded.label] = hole;


	}

	int remove(const int & label)
	{
		if(!IsEmpty())
		{
			//Design was implemented with respect to lecture notes
			// We are not actually deleting an element directly but implicitly
			int value = HeapArray[Location[label]].height;
			int hole = Location[label];
			HeapArray[hole] = HeapArray[currentHeapsize--];
			//It is needed to maintain heap order structure
			percolateDown(hole);
			return value;
		}
		else
		{
			return 0;
		}
	}

	int GetMax()
	{
		if(IsEmpty())
		{
			return 0;
		}
		//If it is not empty then I can send the max element
		return HeapArray[1].height;

	}

	//It is a basic function if it is equal to 0, it means heap is empty.
	//Otherwise, not empty we have at least one element
	bool IsEmpty()
	{
		return currentHeapsize == 0;
	}


};
#endif