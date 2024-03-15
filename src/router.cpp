#include "router.h"
#include "geopoint.h"
#include "HashMap.h"
#include "geotools.h"
#include <vector>
#include <queue>

using namespace std;

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const
{
	vector<GeoPoint> result;

	vector<GeoPoint*> geoPoints;
	vector<Distance*> distances;
	// min heap
	priority_queue<Distance*, vector<Distance*>, GreaterThan> dist_queue;
	HashMap<Distance*> dist_map;
	HashMap<bool> done;

	GeoPoint* pt1_copy = new GeoPoint(pt1);
	Distance* start = new Distance{0, pt1_copy, nullptr};
	geoPoints.push_back(pt1_copy);
	distances.push_back(start);
	dist_queue.push(start);
	dist_map[pt1.to_string()] = start;

	while (!dist_queue.empty()) {
		Distance* curr = dist_queue.top();
		dist_queue.pop();
		done[curr->curr->to_string()] = true;

		if (curr->curr->to_string() == pt2.to_string())
			break;

		vector<GeoPoint> pts = geo->get_connected_points(*(curr->curr));
		for (GeoPoint pt : pts) {
			bool* isDone = done.find(pt.to_string());
			if (isDone != nullptr && *isDone == true)
				continue;

			double miles = distance_earth_miles(*(curr->curr), pt);
			Distance** dist = dist_map.find(pt.to_string());
			if (dist == nullptr) {
				GeoPoint* newGeoPoint = new GeoPoint(pt);
				Distance* newDist = new Distance{curr->dist + miles, newGeoPoint, curr->curr};
				geoPoints.push_back(newGeoPoint);
				distances.push_back(newDist);
				dist_queue.push(newDist);
				dist_map[pt.to_string()] = newDist;
			} else {
				if (curr->dist + miles < (*dist)->dist) {
					(*dist)->dist = curr->dist + miles;
					(*dist)->prev = curr->curr;
				}
			}
		}
	}

	Distance** dist = dist_map.find(pt2.to_string());
	if (dist != nullptr) {
		Distance* d = *dist;
		while (d->curr->to_string() != pt1.to_string()) {
			result.insert(result.begin(), *(d->curr));
			d = dist_map[d->prev->to_string()];
		}
		result.insert(result.begin(), *(d->curr));
	}

	for (Distance* d : distances)
		delete d;

	for (GeoPoint* g : geoPoints)
		delete g;

	return result;
}
