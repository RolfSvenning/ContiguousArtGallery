//#include <CGAL/Constrained_Delaunay_triangulation_2.h>
//#include <CGAL/mark_domain_in_triangulation.h>
//#include <CGAL/Polygon_2.h>
//#include <CGAL/draw_triangulation_2.h>
//#include "CGAL-6.0.1/examples/Triangulation_2/polygon_triangulation_graphics_scene_options.h"

#include <iostream>
#include <cstdlib> // For std::atoi

// For error in CGAL
#include <thread>
#include <future>
#include <vector>
#include <chrono>
#include <stdexcept>

// Mine
#include "Algorithm2.h"
#include "Algorithm1.h"
#include "Helper.h"

// for random polygon
#include <CGAL/random_polygon_2.h>
#include <CGAL/Random.h>
#include <CGAL/point_generators_2.h>
typedef CGAL::Creator_uniform_2<double, Point> PointCreator;
typedef CGAL::Random_points_in_square_2<Point, PointCreator> Point_generator;

//bool tryRandomPolygon(const std::vector<Point>& points, Polygon_2& P) {
//    CGAL::random_polygon_2(points.size(), std::back_inserter(P), points.begin());
//    return true;
//}
//
//Polygon_2 generate_random_polygonNEW(int n, std::optional<int> seed = std::nullopt) {
//    Polygon_2 P;
//    std::vector<Point> points;
//    CGAL::Random rand;
//
//    for (int i = 0; i < 10; ++i) {
//        std::cout << "Attempt: " << i << std::endl;
//        if (seed.has_value()) {
//            std::cout << "has seed" << std::endl;
//            rand = CGAL::Random(seed.value() + i);
//        }
//
//        points.clear();
//        P.clear();
//
//        // Generate unique points
//        CGAL::copy_n_unique(Point_generator(1000, rand), n, std::back_inserter(points));
//
//        // Run random_polygon_2 with a timeout
//        auto future = std::async(std::launch::async, tryRandomPolygon, std::cref(points), std::ref(P));
//
//        if (future.wait_for(std::chrono::seconds(10)) == std::future_status::ready) {
//            if (future.get()) {
//                std::cout << "Random polygon generated successfully on attempt " << i << "." << std::endl;
//                return P; // Return the polygon if successful
//            }
//        } else {
//            std::cout << "Timeout reached on attempt " << i << std::endl;
//        }
//        std::cout << "Attempt " << i << " failed" << std::endl;
//    }
//    std::cout << "Failed to generate random polygon for unknown reasons (bug in CGAL function 'random_polygon_2')" << std::endl;
//    throw std::invalid_argument("");
//    return P;
//}


Polygon_2 generate_random_polygon(int n, std::optional<int> seed = std::nullopt) {
    Polygon_2 P;
    std::vector<Point> points;
    CGAL::Random rand;
    if (seed.has_value()) {
        rand = CGAL::Random(seed.value());
    }
//    std::cout << "Generating random polygon 1" << std::endl;

    CGAL::copy_n_unique(Point_generator(1000, rand), n, std::back_inserter(points));
    CGAL::random_polygon_2(points.size(), std::back_inserter(P), points.begin());

//    std :: cout << "Generating random polygon 3" << std::endl;

    return P;
}

// take input parameter iterations as program parameter
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Not enough parameters provided." << std::endl;
        return 1;
    }

    // Parse input parameters
    int iterations = std::atoi(argv[1]);
    int n = std::atoi(argv[2]);

    // Print the parsed values
//    std::cout << "Running with " << iterations << " iterations and n = " << n << "." << std::endl;
    for (int k = 0; k < iterations; k++) {
//        std::cout << "Iteration: " << k << std::endl;
        // TODO: set seed manually for it to work for small n
        algorithm1(100 * n, polygon_to_arrangement(generate_random_polygon(n, k + rand()))); // spicy seed 404578271
    }

//    Polygon needing 3 guards: https://www.desmos.com/geometry/6iocdgnncv
//    std::vector<Point> points = {Point(0,0), Point(5,-1), Point(4,0), Point(8,-2), Point(8,2), Point(4, 1), Point(6, 4),
//                                     Point(10, 2), Point(8, 8), Point(4, 8), Point(6, 10), Point(0, 10), Point(0, 6), Point(8, 6)};

    // Polygon needing 2 guards: https://www.desmos.com/geometry/ekruamhxwc
//    std::vector<Point> points = {Point(0,0), Point(3, 2), Point(4, 0), Point(4 ,5), Point(1, 2), Point(0, 4)};
//
//    std::vector<Segment> segments;
//    for (int i = 0; i < points.size(); i++) {
//        segments.emplace_back(points[i], points[(i + 1) % points.size()]);
//    }
//
//    Arrangement_2 A;
//    CGAL::insert_non_intersecting_curves(A,segments.begin(),segments.end());
//
//    algorithm1(100 * n, A);

    return 1;
}




//void testPolygonSegmentIntersect() {
////    Segment s1 = Segment(Point(2,2), Point(3,3));
////    Segment s = Segment(Point(0,0), Point(1,1));
//
//    Polygon_2 P, Q, R, S;
//    P.push_back(Point(1, 0));
//    P.push_back(Point(0, 1));
//    P.push_back(Point(0, 0));
//
//    Q.push_back(Point(0, 0));
//    Q.push_back(Point(1, -2));
//    Q.push_back(Point(1, 2));
//
//    R.push_back(Point(-1, -1));
//    R.push_back(Point(2, -2));
//    R.push_back(Point(2, 2));
//    R.push_back(Point(0, 0));
//    R.push_back(Point(1, 1));
//    R.push_back(Point(1, -1));
//
//
//    Polygon_set_2 F;
//    F.insert(P);
//
//    std::cout << "P and Q are: " << std::endl;
//    if (F.do_intersect(Q)) {
//        std::cout << "intersecting" << std::endl;
//        CGAL::draw(polygon_set_to_arrangement(F));
//        F.intersection(Q);
//        CGAL::draw(polygon_set_to_arrangement(F));
//    } else {
//        std::cout << "not intersecting" << std::endl;
//    }
//
//    CGAL::draw(polygon_to_arrangement(R));
//    if (F.do_intersect(R)) {
//        std::cout << "intersecting" << std::endl;
//        CGAL::draw(polygon_set_to_arrangement(F));
//        F.intersection(R);
//        CGAL::draw(polygon_set_to_arrangement(F));
//    } else {
//        std::cout << "not intersecting" << std::endl;
//    }
//
//}

