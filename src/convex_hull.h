//
// Created by shenk on 23.12.23.
//

#ifndef CONVEX_HULL_CONVEX_HULL_H
#define CONVEX_HULL_CONVEX_HULL_H

#include <vector>

struct Point {
    double x = 0.0;
    double y = 0.0;

    bool operator==(const Point &other) const {
        if (this == &other) return true;
        return x == other.x && y == other.y;
    }
};

// | line_point1.x line_point1.y 1 |
// | line_point2.x line_point2.y 1 |
// | point.x       point.y       1 |
double line_position(const Point &point, const Point &line_point1, const Point &line_point2);

std::vector<Point> upper_convex_hull(const std::vector<Point> &points);

void horizontal_mirror(std::vector<Point> &points);

std::vector<Point> lower_convex_hull(std::vector<Point> points);

std::vector<Point> convex_hull(std::vector<Point> points);

#endif //CONVEX_HULL_CONVEX_HULL_H
