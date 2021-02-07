#ifndef _26352_ilkergul_quadtree_H
#define _26352_ilkergul_quadtree_H
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

struct QuadTreeNode
{
	string city;
	double x_coordinate;
	double y_coordinate;
	QuadTreeNode * NorthWest;
	QuadTreeNode * NorthEast;
	QuadTreeNode * SouthWest;
	QuadTreeNode * SouthEast;

	QuadTreeNode()
	{
		x_coordinate = -1;
		y_coordinate = -1;
		NorthWest = NULL;
		NorthEast = NULL;
		SouthWest = NULL;
		SouthEast = NULL;
	}
	QuadTreeNode(const string & cityname, const double & x, const double & y)
	{
		x_coordinate = x;
		y_coordinate = y;
		city = cityname;
		NorthWest = NULL;
		NorthEast = NULL;
		SouthWest = NULL;
		SouthEast = NULL;
	}

	
};


class QuadTree
{
private:
	QuadTreeNode * root;
	double upper_coordinate_x;
	double upper_coordinate_y;

	void insert_private(QuadTreeNode * new_element, QuadTreeNode * & Quad_root);
	void setting_limits(const double & x_cor, const double & y_cor);

	void priv_pretty_print(QuadTreeNode * Quad_root)const;

	void priv_query_search(const double & x,const double & y, const double & radius,
		QuadTreeNode * Quad_root, vector <string> & first_line, vector <string> & second_line);

	void priv_query_main(const double & x, const double & y, const double & radius);
	void priv_query_print(const vector <string> & list)const;

	bool distcirclecalc(const double & x1, const double & y1, const double & x2, const double & y2, const double & radius);
	void cleaning_quadnodes(QuadTreeNode * & head)const;

public:
	QuadTree(); // Constructor
	~QuadTree(); // Destructor

	void insert(const string & city, const double & x, const double & y);
	void pretty_print()const;
	
	void query_search(const double & x,const double & y, const double & radius);
	void set_limit(const double & x_value, const double & y_value);
	
};

#endif