//
// Created by shenk on 23.12.23.
//

#include <gtest/gtest.h>
#include "convex_hull.h"

TEST(LinePosition, ReturnUpper) {
    auto result = line_position(
            {0.5, 0.5},
            {0.0, 0.0},
            {1.0, 0.0}
            );
    ASSERT_GT(result, 0.0);
}

TEST(LinePosition, ReturnLower) {
    auto result = line_position(
            {0.5, -0.5},
            {0.0, 0.0},
            {1.0, 0.0}
    );
    ASSERT_LT(result, 0.0);
}

TEST(LinePosition, ReturnOn) {
    auto result = line_position(
            {0.5, 0.0},
            {0.0, 0.0},
            {1.0, 0.0}
    );
    ASSERT_EQ(result, 0.0);
}

TEST(LinePosition, ReturnUpperNonHorizontal) {
    auto result = line_position(
            {0.5, 0.5},
            {0.0, 0.0},
            {1.0, -1.0}
    );
    ASSERT_GT(result, 0.0);
}

TEST(UpperConvexHull, ThreePoints){
    std::vector<Point> points = {
            {0.0, 0.0},
            {1.0, 2.0},
            {2.0, 0.0}
    };
    auto upper_ch = upper_convex_hull(points);
    ASSERT_EQ(upper_ch, points);
}

TEST(UpperConvexHull, RemoveOne){
    std::vector<Point> points = {
            {0.0, 0.0},
            {1.0, 1.0},
            {2.0, 0.0},
            {3.0, 1.0},
            {4.0, 0.0},
    };
    auto upper_ch = upper_convex_hull(points);
    ASSERT_EQ(upper_ch, std::vector<Point>({
        {0.0, 0.0},
        {1.0, 1.0},
        {3.0, 1.0},
        {4.0, 0.0},
    }));
}

TEST(ConvexHull, Star) {

    std::vector<Point> points =
    {
            {9.5, 5},
            {8.2, 9.5},
            {5.05, 9.45},
            {7.7, 11.4},
            {5.5, 13.7},
            {9, 11.8},
            {11.7, 14.5},
            {10.8, 11.8},
            {14.37, 10.91},
            {10.96, 9.93}
    };

    ASSERT_EQ(convex_hull(points), std::vector<Point>({
                                                              {5.05, 9.45},
                                                              {5.5, 13.7},
                                                              {11.7, 14.5},
                                                              {14.37, 10.91},
                                                              {9.5, 5},
                                                      }));

}