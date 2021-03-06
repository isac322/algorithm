#pragma once

#include <vector>
#include <algorithm>

namespace ConvexHull {
	using namespace std;
	
	const double &PI = 3.14159265358979323846;

	struct Point {
		int x, y;
		double angle = 0.0;

		bool operator<(const Point &val) const {
			if (angle == val.angle) return x < val.x;
			else return angle < val.angle;
		}

		Point() { }

		Point(int x, int y) : x(x), y(y) { }

		Point(const Point &val) : x(val.x), y(val.y), angle(val.angle) { }
	};

	vector<Point> points;


	inline void gen_angle(const Point &base) {
		for (auto &p : points) {
			p.angle = atan2(p.y - base.y, p.x - base.x) * 180 / PI;
		}
	}

	inline long long ccw(const Point &a, const Point &b, const Point &c) {
		long long x1 = a.x, x2 = b.x, x3 = c.x;

		return x2 * c.y - x3 * b.y - (x1 * c.y - x3 * a.y) + x1 * b.y - x2 * a.y;
	}

	vector<Point *> hull;

	vector<Point *> &convex_hull() {
		Point mostLeft = points[0];

		for (auto &d : points) {
			if (mostLeft.y > d.y || (mostLeft.y == d.y && mostLeft.x > d.x)) {
				mostLeft = d;
			}
		}

		gen_angle(mostLeft);
		sort(points.begin(), points.end());


		hull.clear();

		for (auto &p : points) {
			while (hull.size() >= 2 && ccw(*hull[hull.size() - 2], *hull.back(), p) <= 0) {
				hull.pop_back();
			}

			hull.emplace_back(&p);
		}

		return hull;
	}
}