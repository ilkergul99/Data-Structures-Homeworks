#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Stadium_header.h"


/**************************************
Date = 12/25/2020
Cs300 Second Assignment
Purpose = A booking system for a sports stadium

**************************************/
using namespace std;


int main()
{
	string filename = "inputs.txt";
	string outfilename = "output.txt";
	ifstream stadium;
	ofstream outfile;
	outfile.open(outfilename);
	stadium.open(filename);
	if(stadium.is_open())
	{
		if(!stadium.eof())
		{     
			string first_line;								//Here, I am getting the first line
			string getting_blocks;
			vector<string> blockNames;
			getline(stadium, first_line);
			istringstream first_checker(first_line);
			while(first_checker >> getting_blocks)
			{
				blockNames.push_back(getting_blocks);
			}
			if(blockNames.size() >= 2 && !stadium.eof())		//For precaution
			{
				vector<string> RowNames;					//Here, I am getting the second line
				string second_line;
				string getting_rows;
				getline(stadium, second_line);
				istringstream second_checker(second_line);
				while(second_checker >> getting_rows)
				{
					RowNames.push_back(getting_rows);
				}
				if(RowNames.size() >= 2 && !stadium.eof())		//For precaution
				{
					int NumberofColumns;					//Here, I am getting the third line
					string third_line;
					getline(stadium, third_line);
					istringstream third_checker(third_line);
					third_checker >> NumberofColumns;
					if(NumberofColumns >= 2 && !stadium.eof())
					{
						bookingsystem Stadium_bridge(blockNames,RowNames,NumberofColumns);
						string general_line;
						string command, customer_name, block_name, row_name;
						int column_number;
						while(!stadium.eof())
						{
							getline(stadium, general_line);
							if(general_line == "")				// if empty skip it
							{
							
							}
							else if(general_line == "print")		// print the whole booking
							{
								outfile << endl;
								Stadium_bridge.print(blockNames,RowNames,outfile);
							}
							else
							{
								istringstream general(general_line);
								general >> command;
								if(command == "get_seat")			//print the reserved seat
								{
									general >> customer_name;
									Stadium_bridge.get_seat(customer_name, outfile);
									
								}
								else if( command == "cancel_reservation" )		//cancel the reservation
								{
									general >> customer_name;
									Stadium_bridge.cancel_reservation(customer_name, outfile);
								}
								else if( command == "reserve_seat_by_row")		//by row reserve the seat
								{
									general >> customer_name >> row_name;
									Stadium_bridge.reserve_seat_by_row(customer_name, row_name, outfile);
								}
								else											//reserve the seat if empty with parameters
								{
									general >> customer_name >> block_name >> row_name >> column_number;
									Stadium_bridge.reserve_seat(customer_name, block_name, row_name, column_number, outfile);
								}
							}
						}
					}
				}
			}

		}	
	}
	stadium.close();
	outfile.close();		//especially closing the output file is significant
	return 0;
}