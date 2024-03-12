#ifndef geodb_h
#define geodb_h

#include "base_classes.h"
#include "geopoint.h"
#include "HashMap.h"
#include <fstream>
#include <vector>
#include <string>

class GeoDatabase: public GeoDatabaseBase
{
public:
	GeoDatabase() {}
	virtual ~GeoDatabase();
	virtual bool load(const std::string& map_data_file);
	virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;
	virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
	virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;

private:
	int processRecord(std::ifstream& file);

	std::vector<GeoPoint*> geo_points;

	HashMap<GeoPoint*> poi_map;
	HashMap<std::vector<GeoPoint*>> vertex_map;
	HashMap<std::string> street_map;
};

#endif // geodb_h
