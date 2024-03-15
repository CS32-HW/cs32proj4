#ifndef tour_generator_h
#define tour_generator_h

#include "base_classes.h"
#include "tourcmd.h"
#include "stops.h"
#include <string>

class TourGenerator: public TourGeneratorBase
{
public:
	TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router)
	{
		geo = &geodb;
		route = &router;
	}
	virtual ~TourGenerator() {}
	virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;

private:
	std::string getDir(double angle) const;
	const GeoDatabaseBase* geo;
	const RouterBase* route;
};

#endif // tour_generator_h
