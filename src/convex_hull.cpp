//
// Created by shenk on 24.12.23.
//

#include "convex_hull.h"

#include <algorithm>

double line_position(const Point &point, const Point &line_point1, const Point &line_point2) {
    return line_point1.x * (line_point2.y - point.y) -
           line_point1.y * (line_point2.x - point.x) +
           (line_point2.x * point.y - point.x * line_point2.y);
}

std::vector<Point> upper_convex_hull(const std::vector<Point> &points) {
    std::vector<Point> upper_ch = {points[0], points[1]};
    for (int index = 2; index < points.size(); index++) {
        upper_ch.push_back(points[index]);
        while (upper_ch.size() >= 3) {
            bool right_rot = line_position(
                    upper_ch[upper_ch.size() - 2],
                    upper_ch[upper_ch.size() - 3],
                    upper_ch[upper_ch.size() - 1]
            ) < 0.0;
            if (right_rot) { break; }
            upper_ch.erase(upper_ch.end() - 2);
        }
    }
    return upper_ch;
}

void horizontal_mirror(std::vector<Point> &points) {
    for (auto &point: points) {
        point.y *= -1;
    }
}

std::vector<Point> lower_convex_hull(std::vector<Point> points) {
    horizontal_mirror(points);
    auto upper_ch = upper_convex_hull(points);
    horizontal_mirror(upper_ch);
    return upper_ch;
}

std::vector<Point> convex_hull(std::vector<Point> points) {

    std::sort(points.begin(), points.end(), [](const auto &lh, const auto rh) {
        if (lh.x == rh.x) {
            return lh.y < rh.y;
        }
        return lh.x < rh.x;
    });

    auto left = points.front();
    points.erase(points.begin());

    auto right = points.back();
    points.erase(std::prev(points.end()));

    std::vector<Point> upper = {left,};
    std::vector<Point> lower = {left,};
    for (const auto &point: points) {
        if (line_position(point, left, right) < 0) {
            upper.push_back(point);
        } else {
            lower.push_back(point);
        }
    }

    upper.push_back(right);
    auto upper_ch = upper_convex_hull(upper);

    lower.push_back(right);
    auto lower_ch = lower_convex_hull(lower);

    auto convex_hull = lower_ch;
    convex_hull.insert(convex_hull.end(), std::next(upper_ch.rbegin()), std::prev(upper_ch.rend()));

    return convex_hull;
}
