#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "26352-ilkergul-quadtree.h"

/**************************************
Date = 11/27/2020
Cs300 Second Assignment
Purpose = Implement a point quadtree of cities

**************************************/
using namespace std;


int main()
{
	string filename_cities = "cities.txt";
	ifstream input_cities;


	input_cities.open(filename_cities);
	if(input_cities.is_open())
	{
		double cities_x_coordinate, endpoint_x_coordinate;
		double cities_y_coordinate, endpoint_y_coordinate;
		string cityname, line, x_axis, y_axis;
		QuadTree Maintree;

		getline(input_cities, line);
		istringstream first_line(line);
		first_line >> endpoint_x_coordinate >>endpoint_y_coordinate ;
		Maintree.set_limit(endpoint_x_coordinate, endpoint_y_coordinate);
		while(!input_cities.eof())
		{
			getline(input_cities, line);
			istringstream component_check(line);
			component_check >> cityname >> x_axis >> y_axis;

			int n = x_axis.rfind(',');
			if(n != -1)
			{
				x_axis.erase(n,1);
			}
			n =y_axis.rfind(',');
			if(n != -1)
			{
				y_axis.erase(n,1);
			}
			cities_x_coordinate = stod(x_axis);
			cities_y_coordinate = stod(y_axis);

			if(cities_x_coordinate < 0 || cities_y_coordinate < 0 )
			{

			}
			else if(cities_x_coordinate > endpoint_x_coordinate 
				|| cities_y_coordinate > endpoint_y_coordinate)
			{

			}

			else
			{
				Maintree.insert(cityname, cities_x_coordinate, cities_y_coordinate);
			}
		}

		Maintree.pretty_print();
		

		/*---------------------- query part ----------------------------------*/

		string filename_queries = "queries.txt";
		ifstream input_queries;
		input_queries.open(filename_queries);

		if(input_queries.is_open())
		{
			string line2;
			string query_x_coordinate, query_y_coordinate;
			double query_x, query_y;
			double radius;
			while(!input_queries.eof())
			{
				getline(input_queries, line2);
				istringstream query_checker(line2);
				query_checker >> query_x_coordinate >> query_y_coordinate >> radius;

				int n = query_x_coordinate.rfind(',');
				query_x_coordinate.erase(n,1);
				n = query_y_coordinate.rfind(',');
				query_y_coordinate.erase(n,1);
				query_x = stod(query_x_coordinate);
				query_y = stod(query_y_coordinate);

				if(query_x < 0 || query_y < 0)
				{
					cout << "\nQuery coordinate's values cannot assume negative values!" << endl;
					
				}
				else
				{
					cout << endl;
					Maintree.query_search(query_x, query_y, radius);				
				}
				

			}
		}
	}

	return 0;
}