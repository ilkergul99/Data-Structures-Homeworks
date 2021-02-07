#include "26352-ilkergul-quadtree.h"

using namespace std;

QuadTree::QuadTree() // Constructor
{
	root = NULL;
	upper_coordinate_x = 0;
	upper_coordinate_y = 0;
}

QuadTree::~QuadTree() // Destructor
{
	cleaning_quadnodes(root);
}

// This one is cleaning the quadtree nodes recursively
void QuadTree::cleaning_quadnodes(QuadTreeNode * & head)const
{
	if(head != NULL)
	{
		cleaning_quadnodes(head->NorthWest);
		cleaning_quadnodes(head->NorthEast);
		cleaning_quadnodes(head->SouthWest);
		cleaning_quadnodes(head->SouthEast);
		delete head;
	}
	head = NULL;
}



void QuadTree::set_limit(const double & x, const double & y) // public getting boundaries
{
	setting_limits(x, y);
}

void QuadTree::setting_limits(const double & x_cor, const double & y_cor) // private setting boundaries
{
	upper_coordinate_x = x_cor;
	upper_coordinate_y = y_cor;
}

// This is the public version of the insert call, I am using private function in reality
void QuadTree::insert(const string & city, const double & x, const double & y) //public insert
{
	QuadTreeNode * New_Node = new QuadTreeNode(city, x , y);
	insert_private(New_Node, root);
}

// This is the version of the private insert, I am using a recurive approach to insert
void QuadTree::insert_private(QuadTreeNode * new_element, QuadTreeNode * & Quad_root) //private insert
{
	if(new_element != NULL)
	{
		if(Quad_root == NULL)
		{
			Quad_root = new_element;
		}
		else
		{
			if(new_element->x_coordinate == Quad_root->x_coordinate && new_element->y_coordinate == Quad_root->y_coordinate )
			{
				
			}

			else if(new_element->x_coordinate < Quad_root->x_coordinate)
			{
				if(new_element->y_coordinate < Quad_root->y_coordinate)
				{
					insert_private(new_element, Quad_root->SouthWest);
				}
				else
				{
					insert_private(new_element, Quad_root->NorthWest);
				}
			}
			else if(new_element->y_coordinate < Quad_root->y_coordinate)
			{
				insert_private(new_element, Quad_root->SouthEast);
			}
			else
			{
				insert_private(new_element, Quad_root->NorthEast);
			}

		}
	}
}

void QuadTree::query_search(const double & x, const double & y,const double & radius)
{
	if(x > upper_coordinate_x || y > upper_coordinate_y)
	{
		
	}
	else
	{
		priv_query_main(x,y,radius);
	}
}

// Main private query function which calls helper functions to do necessary tasks
// I am going to have a search function. Then,
// I will print first and second line with the vector that I have defined
void QuadTree::priv_query_main(const double & x, const double & y, const double & radius)
{
	vector <string> first_line;
	vector <string> second_line;
	priv_query_search(x, y, radius, root, first_line, second_line);
	priv_query_print(first_line);
	priv_query_print(second_line);
	
}

//I am printing the stored elements in a string vector if there is no element
//It will print <None>
void QuadTree::priv_query_print(const vector<string> & list)const
{
	if(list.size() == 0)
	{
		cout << "<None>" << endl;
	}
	else
	{
		for(int i = 0; i < list.size(); i++)
		{
			if(i != list.size() - 1)
			{
				cout << list.at(i) << ", ";
			}
			else
			{
				cout << list.at(i) << endl;
			}
		}
	}
}


void QuadTree::priv_query_search(const double & x, const double & y, const double & radius, 
								 QuadTreeNode * Quad_root, vector <string> & first_line, vector <string> & second_line)
{

	// I need to check 13 cases
	if(Quad_root != NULL)
	{
		second_line.push_back(Quad_root->city);

		// Case 13
		if(distcirclecalc(x,y, Quad_root->x_coordinate, Quad_root->y_coordinate, radius))
		{
			first_line.push_back(Quad_root->city);

			priv_query_search(x,y, radius, Quad_root->SouthEast, first_line, second_line);
			priv_query_search(x,y, radius, Quad_root->SouthWest, first_line, second_line);
			priv_query_search(x,y, radius, Quad_root->NorthEast, first_line, second_line);
			priv_query_search(x,y, radius, Quad_root->NorthWest, first_line, second_line);
		}
		else
		{
			if(Quad_root->x_coordinate > (x + radius)) // Case 3, 5 and 8
			{
				if(Quad_root->y_coordinate < (y-radius)) // Case 8
				{
					priv_query_search(x,y, radius, Quad_root->NorthWest, first_line, second_line);
				}

				else if(Quad_root->y_coordinate > (y + radius)) // Case 3
				{
					priv_query_search(x,y, radius, Quad_root->SouthWest, first_line, second_line);
				}

				else // Case 5
				{
					priv_query_search(x,y, radius, Quad_root->SouthWest, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->NorthWest, first_line, second_line);
				}
			}

			else if(Quad_root->x_coordinate < (x - radius)) // Case 1, 4 and 6
			{
				if(Quad_root->y_coordinate < (y-radius)) // Case 6
				{
					priv_query_search(x,y, radius, Quad_root->NorthEast, first_line, second_line);
				}

				else if(Quad_root->y_coordinate > (y + radius)) // Case 1
				{
					priv_query_search(x,y, radius, Quad_root->SouthEast, first_line, second_line);
				}

				else // Case 4
				{
					priv_query_search(x,y, radius, Quad_root->SouthEast, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->NorthEast, first_line, second_line);
				}
			}
			else // Case 2, 7, 9, 10, 11, 12
			{
				if(Quad_root->y_coordinate > (y + radius)) // Case 2
				{
					priv_query_search(x,y, radius, Quad_root->SouthEast, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->SouthWest, first_line, second_line);
				}

				else if(Quad_root->y_coordinate < (y - radius)) //Case 7
				{
					priv_query_search(x,y, radius, Quad_root->NorthEast, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->NorthWest, first_line, second_line);
				}

				else if(Quad_root->y_coordinate >= y && Quad_root->y_coordinate <= (y + radius) 
					&& Quad_root->x_coordinate >= (x - radius) && Quad_root->x_coordinate < x ) //Case 9
				{
					priv_query_search(x,y, radius, Quad_root->SouthEast, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->SouthWest, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->NorthEast, first_line, second_line);

				}

				else if(Quad_root->y_coordinate < y && Quad_root->y_coordinate >= (y - radius) 
					&& Quad_root->x_coordinate >= (x - radius) && Quad_root->x_coordinate < x ) //Case 11
				{
					priv_query_search(x,y, radius, Quad_root->SouthEast, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->NorthEast, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->NorthWest, first_line, second_line);

				}

				else if(Quad_root->y_coordinate >= y && Quad_root->y_coordinate <= (y + radius) 
					&& Quad_root->x_coordinate <= (x + radius) && Quad_root->x_coordinate >= x ) //Case 10
				{
					priv_query_search(x,y, radius, Quad_root->SouthEast, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->SouthWest, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->NorthWest, first_line, second_line);

				}
				else // Case 12
				{
					priv_query_search(x,y, radius, Quad_root->SouthWest, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->NorthEast, first_line, second_line);
					priv_query_search(x,y, radius, Quad_root->NorthWest, first_line, second_line);
				}

			}


		}
	}
}

//Here, I am calculating the distance between query point and related city
// whether the distance is bigger than radius or not
bool QuadTree::distcirclecalc(const double & x1, const double & y1, const double & x2, const double & y2, const double & radius)
{
	double final_value = pow((x1 - x2),2) + pow((y1 - y2), 2);
	if(final_value <= radius*radius)
	{
		return true;
	}
	else
	{
		return false;
	}

}

// I am calling the private print function
void QuadTree::pretty_print()const
{
	priv_pretty_print(root);
}

// Recursive print function which is specified in the assignment guideline
void QuadTree::priv_pretty_print(QuadTreeNode * Quad_root)const
{
	if(Quad_root != NULL)
	{
		cout << Quad_root->city << endl;
		priv_pretty_print(Quad_root->SouthEast);
		priv_pretty_print(Quad_root->SouthWest);
		priv_pretty_print(Quad_root->NorthEast);
		priv_pretty_print(Quad_root->NorthWest);
	}
}



