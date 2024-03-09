#include "geodb.h"
#include "geopoint.h"
#include <cassert>

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
}

int main()
{
	test1();
}
