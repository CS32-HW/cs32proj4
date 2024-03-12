#ifndef router_h
#define router_h

#include "base_classes.h"
#include <vector>

class Router: public RouterBase
{
public:
	Router(const GeoDatabaseBase& geo_db) { geo = &geo_db; }
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;

private:
	const GeoDatabaseBase* geo;
};

#endif // router_h
