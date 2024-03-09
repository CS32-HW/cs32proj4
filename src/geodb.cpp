#include "geodb.h"
#include "geotools.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>

using namespace std;

GeoDatabase::~GeoDatabase()
{
	for (int i = 0; i < geo_points.size(); i++)
		delete geo_points[i];
}

bool GeoDatabase::load(const std::string& map_data_file)
{
	ifstream file(map_data_file);
	if (!file) {
		cerr << "no map file found" << endl;
		return false;
	}

	int lineNumber;
	while (true) {
		int num = processRecord(file);
		if (num == 0)
			break;

		if (num == -1) {
			cerr << "incomplete record at line " << lineNumber << endl;
			return false;
		}

		lineNumber += num;
	}

	cerr << "processed " << lineNumber << " lines from " << map_data_file << endl;
	return true;
}

int GeoDatabase::processRecord(std::ifstream& file)
{
	string streetName;
	if (!getline(file, streetName))
		return 0;

	string geoPoints;
	if (!getline(file, geoPoints))
		return -1;

	string coor[4];
	int start = 0, end = 0;
	for (int i = 0; i < 3; i++) {
		end = geoPoints.find(" ", start);
		coor[i] = geoPoints.substr(start, end);
		start = end+1;
	}
	coor[3] = geoPoints.substr(start);

	GeoPoint* pt1 = new GeoPoint(coor[0], coor[1]);
	GeoPoint* pt2 = new GeoPoint(coor[2], coor[3]);
	GeoPoint* mid = new GeoPoint;
	*mid = midpoint(*pt1, *pt2);

	geo_points.push_back(pt1);
	geo_points.push_back(pt2);
	geo_points.push_back(mid);

	vertex_map[pt1->to_string()].push_back(pt2);
	vertex_map[pt1->to_string()].push_back(mid);
	vertex_map[mid->to_string()].push_back(pt1);
	vertex_map[mid->to_string()].push_back(pt2);
	vertex_map[pt2->to_string()].push_back(pt1);
	vertex_map[pt2->to_string()].push_back(mid);

	street_map[pt1->to_string() + ","  + pt2->to_string()] = streetName;
	street_map[pt1->to_string() + ","  + mid->to_string()] = streetName;
	street_map[mid->to_string() + ","  + pt1->to_string()] = streetName;
	street_map[mid->to_string() + ","  + pt2->to_string()] = streetName;
	street_map[pt2->to_string() + ","  + pt1->to_string()] = streetName;
	street_map[pt2->to_string() + ","  + mid->to_string()] = streetName;

	string strNumPOI;
	if (!getline(file, strNumPOI))
		return -1;
	int numPOI = stoi(strNumPOI);

	for (int i = 0; i < numPOI; i++) {
		string poi;
		if (!getline(file, poi))
			return -1;

		int delim_loc = poi.find("|", 0);
		string poi_name = poi.substr(0, delim_loc);
		string poi_coor = poi.substr(delim_loc+1);
		string poi_lat = poi_coor.substr(0, poi_coor.find(" ", 0));
		string poi_lon = poi_coor.substr(poi_coor.find(" ", 0)+1);

		GeoPoint* geoPoint = new GeoPoint(poi_lat, poi_lon);
		geo_points.push_back(geoPoint);

		poi_map[poi_name] = geoPoint;

		vertex_map[geoPoint->to_string()].push_back(mid);
		vertex_map[mid->to_string()].push_back(geoPoint);

		street_map[geoPoint->to_string() + "," + mid->to_string()] = "a path";
		street_map[mid->to_string() + "," + geoPoint->to_string()] = "a path";
	}

	return 3 + numPOI;
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const
{
	GeoPoint* const* ptr = poi_map.find(poi);

	if (ptr == nullptr)
		return false;

	point = **ptr;
	return true;
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const
{
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const
{
}
