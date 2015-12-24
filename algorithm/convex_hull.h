#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

namespace ConvexHull {
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

	std::vector<Point> points;


	inline void gen_angle(const Point &base) {
		for (auto &p : points) {
			p.angle = atan2(p.y - base.y, p.x - base.x) * 180 / M_PI;
		}
	}

	inline long long ccw(const Point &a, const Point &b, const Point &c) {
		long long x1 = a.x, x2 = b.x, x3 = c.x;

		return x2 * c.y - x3 * b.y - (x1 * c.y - x3 * a.y) + x1 * b.y - x2 * a.y;
	}

	std::vector<Point *> hull;

	std::vector<Point *> &convex_hull() {
		Point mostLeft = points[0];

		for (auto &d : points) {
			if (mostLeft.y > d.y || (mostLeft.y == d.y && mostLeft.x > d.x)) {
				mostLeft = d;
			}
		}

		gen_angle(mostLeft);
		std::sort(points.begin(), points.end());


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