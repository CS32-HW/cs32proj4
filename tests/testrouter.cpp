#include "../src/router.h"
#include "../src/geodb.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

GeoDatabase g;

void test1()
{
	Router router(g);
	vector<GeoPoint> test = router.route(GeoPoint("34.0569695", "-118.4646643"), GeoPoint("34.0732843", "-118.4487927"));

	assert(test.size() == 122);
	assert(test[0].to_string() == "34.0569695,-118.4646643");
	assert(test[3].to_string() == "34.0559335,-118.4636610");
	assert(test[121].to_string() == "34.0732843,-118.4487927");

	cout << "test1 passed" << endl;
}

void test2()
{
	Router router(g);
	vector<GeoPoint> test = router.route(GeoPoint("34.0569695", "-118.4646643"), GeoPoint());

	assert(test.size() == 0);

	cout << "test2 passed" << endl;
}

void test3()
{
	Router router(g);
	vector<GeoPoint> test = router.route(GeoPoint("34.0569695", "-118.4646643"), GeoPoint("34.0737377", "-118.4453250"));

	assert(test.size() == 143);
	assert(test[0].to_string() == "34.0569695,-118.4646643");
	assert(test[3].to_string() == "34.0559335,-118.4636610");
	assert(test[142].to_string() == "34.0737377,-118.4453250");

	cout << "test3 passed" << endl;
}

int main()
{
	g.load("../mapdata.txt");
	test1();
	test2();
	test3();
	cout << "testrouter: all tests passed" << endl;
}
