#ifndef router_h
#define router_h

#include "base_classes.h"
#include "geopoint.h"
#include <vector>

class Router: public RouterBase
{
public:
	Router(const GeoDatabaseBase& geo_db) { geo = &geo_db; }
	virtual ~Router() {}
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;

private:
	struct Distance {
		double dist;
		const GeoPoint* curr;
		const GeoPoint* prev;
	};

	struct GreaterThan {
		bool operator()(const Distance* a, const Distance* b) const
		{
			return a->dist > b->dist;
		}
	};

	const GeoDatabaseBase* geo;
};

#endif // router_h
