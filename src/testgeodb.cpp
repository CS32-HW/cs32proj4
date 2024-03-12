#include "geodb.h"
#include "geopoint.h"
#include <cassert>
#include <iostream>

using namespace std;

void test1()
{
	GeoDatabase g;
	g.load("../mapdata.txt");
	GeoPoint p;
	assert(g.get_poi_location("Diddy Riese", p) == true);
	assert(p.to_string() == "34.0630614,-118.4468781");
	assert(g.get_poi_location("Your mom's house", p) == false);
	assert(p.to_string() == "34.0630614,-118.4468781");
	assert(g.get_poi_location("Ackerman Union", p) == true);
	assert(p.to_string() == "34.0705851,-118.4439429");
	assert(g.get_poi_location("Elysee", p) == true);
	assert(p.to_string() == "34.0602814,-118.4467380");


	vector<GeoPoint> pts = g.get_connected_points(GeoPoint("34.0736122", "-118.4927669"));

	for (int i = 0; i < pts.size(); i++)
		cout << pts[i].to_string() << endl;

	GeoPoint pt1("34.0582358", "-118.4421816");
	GeoPoint pt2("34.0572000", "-118.4417620");
	cout << g.get_street_name(pt1, pt2) << endl;

	cout << "test1 passed" << endl;
}

int main()
{
	test1();
}
