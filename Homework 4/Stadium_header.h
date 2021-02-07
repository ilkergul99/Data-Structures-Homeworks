#ifndef Stadium_Header
#define Stadium_Header

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

struct customerinfo
{
	string Block_name;
	string Row_name;
	int column_NO;

	customerinfo()
	{
		column_NO = -1;
	}
	customerinfo(const string & Bname, const string & Rname, const int & Cnumber)
	{
		Block_name = Bname;
		Row_name = Rname;
		column_NO = Cnumber;
	}
};

struct binaryheap
{
	string blockname;		// to specify the blockname 
	int label;				// label to the blockname to differentiate
	int emptysize;			// empty slot size of a row in a certain block

	binaryheap()
	{
		label = -1;
		emptysize = -1;
	}
	binaryheap(const string & name, const int & blocklabel, const int & emptysizelabel)
	{
		blockname = name;
		label = blocklabel;
		emptysize = emptysizelabel;
	}

};


class bookingsystem
{
private:
	unordered_map<string, unordered_map<string, vector<string>>> stadium_booking;
	int block_size ;
	int row_size;
	int column_size;
	unordered_map<string, customerinfo> personal_information;
	unordered_map<string, vector<binaryheap>> HeapForAllRows;
	unordered_map<string,unordered_map<string,int>> Location; //row name, blockname, indexofthevector;

	//We are gonna need priority queue, I guess  to get O( logB )
protected:
	void percolatedown(const string & rowname, const int & index)
	{
		binaryheap temp = HeapForAllRows[rowname].at(index);
		int hole = index;
		int child;
		for(; hole*2 <= block_size ; hole = child)
		{
			child = 2*hole;
			if(child != block_size && (HeapForAllRows[rowname].at(child + 1).emptysize > HeapForAllRows[rowname].at(child).emptysize ||
				HeapForAllRows[rowname].at(child + 1).emptysize >= HeapForAllRows[rowname].at(child).emptysize && 
				HeapForAllRows[rowname].at(child + 1).label < HeapForAllRows[rowname].at(child).label ))
			{
				child++;
			}
			if(HeapForAllRows[rowname].at(child).emptysize > temp.emptysize || 
				(HeapForAllRows[rowname].at(child).emptysize >= temp.emptysize && HeapForAllRows[rowname].at(child).label < temp.label))
			{
				HeapForAllRows[rowname].at(hole) = HeapForAllRows[rowname].at(child);
				Location[rowname][HeapForAllRows[rowname].at(hole).blockname] = hole;
			}
			else
			{
				break;
			}
		}
		HeapForAllRows[rowname].at(hole) = temp;
		Location[rowname][temp.blockname] = hole;
	}

	void percolateup(const string & rowname, const int & index)
	{
		binaryheap temp = HeapForAllRows[rowname].at(index);
		int hole = index;
		for(; hole > 1 && (HeapForAllRows[rowname].at(hole/2).emptysize < temp.emptysize || 
				(HeapForAllRows[rowname].at(hole/2).emptysize <= temp.emptysize && HeapForAllRows[rowname].at(hole/2).label > temp.label)); hole /=2 )
		{
			HeapForAllRows[rowname].at(hole) = HeapForAllRows[rowname].at(hole/2);
			Location[rowname][HeapForAllRows[rowname].at(hole).blockname] = hole;
		}
		HeapForAllRows[rowname].at(hole) = temp;
		Location[rowname][temp.blockname] = hole;
	}
	

public:
	//Default constructor
	bookingsystem()
	{
		block_size = 0;
		row_size = 0;
		column_size = 0;
	}
	

	//Constructor with parameter
	bookingsystem( vector<string> & block_name, vector< string> & row_name, const int & column_number)
	{
		block_size = block_name.size();
		row_size = row_name.size();
		column_size = column_number;
		
		string block_title;
		string row_title;
		vector<string> customer_names(column_number, "---");
		for(int i = 0; i < block_name.size(); i++)
		{
			block_title = block_name.at(i);
			stadium_booking[block_title];
			for(int j = 0; j < row_name.size(); j++)
			{
				row_title = row_name.at(j);
				stadium_booking[block_title][row_title] = customer_names;

			}
		}
		for(int a = 0; a < row_size; a++)
		{
			binaryheap junkvalue;
			HeapForAllRows[row_name.at(a)].push_back(junkvalue);
			Location[row_name.at(a)];
			for(int k = 0; k < block_size; k++)
			{
				binaryheap Gonnabeadded(block_name.at(k), k+1, column_size);
				HeapForAllRows[row_name.at(a)].push_back(Gonnabeadded);
				Location[row_name.at(a)][block_name.at(k)] = k + 1;
			}
		}
	}
	
	// Time Complexity should be O( logB )
	void cancel_reservation(const string & customer_name, ofstream & file)
	{
		if(personal_information.find(customer_name) == personal_information.end())
		{
			file << "Could not cancel the reservation for " << customer_name << "; no reservation found!" << endl; 
		}
		else
		{
			stadium_booking[personal_information[customer_name].Block_name][personal_information[customer_name].Row_name].at(personal_information[customer_name].column_NO) = "---";
			//We need to perform percolate up if the index in the heap is different than 1
			HeapForAllRows[personal_information[customer_name].Row_name].at(Location[personal_information[customer_name].Row_name].at(personal_information[customer_name].Block_name)).emptysize += 1;
			percolateup(personal_information[customer_name].Row_name, Location[personal_information[customer_name].Row_name].at(personal_information[customer_name].Block_name));
			personal_information.erase(customer_name); 
			file << "Cancelled the reservation of " << customer_name << endl;
		}

	}
	

	// Time complexity is O( 1 )
	void get_seat(const string & customer_name, ofstream & file)
	{
		if(personal_information.find(customer_name) == personal_information.end())
		{
			file << "There is no reservation made for " << customer_name << "!" << endl; 
		}
		else
		{
			file << "Found that " << customer_name << " has a reservation in " << personal_information[customer_name].Block_name << " "
			<< personal_information[customer_name].Row_name << "-" << personal_information[customer_name].column_NO << endl;
		}
	}

	
	// Time complexity is O( logB )
	void reserve_seat(const string & customer_name, const string & block_name, const string & row_name, const int & column_number, ofstream & file)
	{
		if(personal_information.find(customer_name) != personal_information.end())
		{
			file << customer_name << " could not reserve a seat!" << endl; 
		}
		else
		{
			if(stadium_booking[block_name][row_name].at(column_number) == "---")
			{
				stadium_booking[block_name][row_name].at(column_number) = customer_name.substr(0,3);
				personal_information[customer_name] = customerinfo(block_name, row_name, column_number);
				HeapForAllRows[row_name].at(Location[row_name].at(block_name)).emptysize -= 1;
				percolatedown(row_name, Location[row_name].at(block_name));
    			file << customer_name << " has reserved " << block_name << " " << row_name <<"-" << column_number << endl;
			}
			else
			{
				file << customer_name << " could not reserve a seat!" << endl;
			}
		}
	}
	

	// Time complexity is O( B*R*C )
	void print(vector<string> & block_name, vector< string> & row_name, ofstream & file)
	{
		for(int i = 0; i < block_name.size(); i++)
		{
			file << block_name.at(i) << endl;
			file << "~~~~~~~" << endl;
			for(int j = 0; j < row_size; j++)
			{
				file << row_name.at(j) << " : ";
				for(int k = 0; k < column_size; k++)
				{
					if(k == column_size -1)
					{
						file << stadium_booking[block_name.at(i)][row_name.at(j)].at(k) << endl;
					}
					else
					{
						file << stadium_booking[block_name.at(i)][row_name.at(j)].at(k) << " " ;
					}
				}
			}
			file << "=======" << endl << endl;
		}
	}
	

	// Time complexity is O( logB + C)
	void reserve_seat_by_row(const string & customer_name, const string & row_name, ofstream & file)
	{
		// if already have one then print could not reserve
		if(personal_information.find(customer_name) != personal_information.end())
		{
			file << customer_name << " could not reserve a seat!" << endl; 
		}
		else
		{
			// if no empty places, print could not reserve
			if(HeapForAllRows[row_name].at(1).emptysize == 0)
			{
				file << customer_name << " could not reserve a seat!" << endl; 
			}
			//We can print and percolate the heap with necessary modifications
			else
			{
				for(int i = 0; i < column_size; i++)
				{
					if(stadium_booking[HeapForAllRows[row_name].at(1).blockname][row_name].at(i) == "---")
					{
						stadium_booking[HeapForAllRows[row_name].at(1).blockname][row_name].at(i) = customer_name.substr(0,3);
						personal_information[customer_name] = customerinfo(HeapForAllRows[row_name].at(1).blockname, row_name, i);
						string block = HeapForAllRows[row_name].at(1).blockname;
						HeapForAllRows[row_name].at(Location[row_name].at(block)).emptysize -= 1;
						
						percolatedown(row_name, 1);
						file << customer_name << " has reserved " << block << " " << row_name 
							<<"-" << i << " by emptiest block" << endl;
						break;
					}
				}
			}
			
		}
	}

};

#endif