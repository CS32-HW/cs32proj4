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

	assert(test.size() == 123);
	assert(test[0].to_string() == "34.0569695,-118.4646643");
	assert(test[122].to_string() == "34.0732843,-118.4487927");

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

	assert(test.size() == 144);
	assert(test[0].to_string() == "34.0569695,-118.4646643");
	assert(test[143].to_string() == "34.0737377,-118.4453250");

	cout << "test3 passed" << endl;
}

void test4()
{
	Router router(g);
	vector<GeoPoint> test = router.route(GeoPoint("34.0569695", "-118.4646643"), GeoPoint("34.0569695", "-118.4646643"));

	assert(test.size() == 1);
	assert(test[0].to_string() == "34.0569695,-118.4646643");

	cout << "test4 passed" << endl;
}

void tmp()
{
	GeoDatabase gtest;
	gtest.load("testmap.txt");
	Router router(gtest);
	vector<GeoPoint> test = router.route(GeoPoint("0.5000000", "0.1000000"), GeoPoint("1.5000000", "0.1000000"));

	assert(test.size() == 5);
	assert(test[0].to_string() == "0.5000000,0.1000000");
	assert(test[4].to_string() == "1.5000000,0.1000000");

	//for (auto pt : test)
	//	cout << pt.to_string() << endl;
}

int main()
{
	g.load("../mapdata.txt");
	test1();
	test2();
	test3();
	test4();
	tmp();
	cout << "testrouter: all tests passed" << endl;
}
