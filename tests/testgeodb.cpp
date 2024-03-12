#include "../src/geodb.h"
#include "../src/geopoint.h"
#include <cassert>
#include <iostream>

using namespace std;

GeoDatabase g;

void test1()
{
	GeoPoint p;
	assert(g.get_poi_location("Diddy Riese", p) == true);
	assert(p.to_string() == "34.0630614,-118.4468781");
	assert(g.get_poi_location("Your mom's house", p) == false);
	assert(p.to_string() == "34.0630614,-118.4468781");
	assert(g.get_poi_location("Ackerman Union", p) == true);
	assert(p.to_string() == "34.0705851,-118.4439429");
	assert(g.get_poi_location("Elysee", p) == true);
	assert(p.to_string() == "34.0602814,-118.4467380");
	cout << "test1 passed" << endl;
}

void test2()
{
	vector<GeoPoint> pts1 = g.get_connected_points(GeoPoint("34.0736122", "-118.4927669"));
	string expected1[3] = {
		"34.0732851,-118.4931016",
		"34.0731714,-118.4921918",
		"34.0739890,-118.4931789",
	};
	for (int i = 0; i < pts1.size(); i++)
		assert(pts1[i].to_string() == expected1[i]);

	vector<GeoPoint> pts2 = g.get_connected_points(GeoPoint("34.0601422", "-118.4468929"));
	string expected2 = "34.0600768,-118.4467216";
	assert(pts2.size() == 1 && pts2[0].to_string() == expected2);

	vector<GeoPoint> pts3 = g.get_connected_points(GeoPoint("34.0600768", "-118.4467216"));
	string expected3[4] = {
		"34.0602175,-118.4464952",
		"34.0599361,-118.4469479",
		"34.0601422,-118.4468929",
		"34.0591552,-118.4463759",
	};
	for (int i = 0; i < pts3.size(); i++)
		assert(pts3[i].to_string() == expected3[i]);

	cout << "test2 passed" << endl;
}

void test3()
{
	GeoPoint pt1("34.0732851", "-118.4931016");
	GeoPoint pt2("34.0736122", "-118.4927669");
	string res1 = g.get_street_name(pt1, pt2);
	string res2 = g.get_street_name(pt2, pt1);
	assert(res1 == "Glenmere Way" && res1 == res2);

	GeoPoint pt3("34.0601422", "-118.4468929");
	GeoPoint pt4("34.0600768", "-118.4467216");
	assert(g.get_street_name(pt3, pt4) == "a path");
	assert(g.get_street_name(pt4, pt3) == "a path");

	GeoPoint pt5("34.0602175", "-118.4464952");
	GeoPoint pt6("34.0600768", "-118.4467216");
	assert(g.get_street_name(pt5, pt6) == "Kinross Avenue");
	assert(g.get_street_name(pt6, pt5) == "Kinross Avenue");

	cout << "test3 passed" << endl;
}

int main()
{
	g.load("../mapdata.txt");
	test1();
	test2();
	test3();
	cout << "testgeodb: all tests passed" << endl;
}
