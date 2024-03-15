#include "tour_generator.h"
#include "tourcmd.h"
#include "stops.h"
#include "geopoint.h"
#include "geotools.h"

using namespace std;

vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const
{
	vector<TourCommand> result;

	for (int i = 0; i < stops.size(); i++) {
		string poi, talking_points;
		stops.get_poi_data(i, poi, talking_points);

		TourCommand tc;
		tc.init_commentary(poi, talking_points);
		result.push_back(tc);

		if (i+1 < stops.size()) {
			string dest_poi;
			stops.get_poi_data(i+1, dest_poi, talking_points);

			GeoPoint pt1;
			GeoPoint pt2;
			if (!geo->get_poi_location(poi, pt1) ||
					!geo->get_poi_location(dest_poi, pt2)) {
				cerr << "point of interest not found" << endl;
				result.clear();
				return result;
			}

			vector<GeoPoint> path = route->route(pt1, pt2);
			if (path.size() == 0) {
				cerr << "route not found" << endl;
				result.clear();
				return result;
			}

			for (int j = 1; j < path.size(); j++) {
				TourCommand tc2;
				tc2.init_proceed(getDir(angle_of_line(path[j-1], path[j])),
						geo->get_street_name(path[j-1], path[j]),
						distance_earth_miles(path[j-1], path[j]),
						path[j-1], path[j]);
				result.push_back(tc2);

				if (j+1 < path.size() &&
						geo->get_street_name(path[j-1], path[j]) != geo->get_street_name(path[j], path[j+1]) &&
						angle_of_turn(path[j-1], path[j], path[j+1]) != 0) {
					TourCommand turn;
					double angle = angle_of_turn(path[j-1], path[j], path[j+1]);
					turn.init_turn((1 <= angle && angle < 180) ? "left" : "right",
							geo->get_street_name(path[j], path[j+1]));
					result.push_back(turn);
				}

			}
		}
	}

	return result;
}

string TourGenerator::getDir(double angle) const
{
	if (0 <= angle && angle < 22.5)
		return "east";
	else if (22.5 <= angle && angle < 67.5)
		return "northeast";
	else if (67.5 <= angle && angle < 112.5)
		return "north";
	else if (112.5 <= angle && angle < 157.5)
		return "northwest";
	else if (157.5 <= angle && angle < 202.5)
		return "west";
	else if (202.5 <= angle && angle < 247.5)
		return "southwest";
	else if (247.5 <= angle && angle < 292.5)
		return "south";
	else if (292.5 <= angle && angle < 337.5)
		return "southeast";
	else
		return "east";
}
