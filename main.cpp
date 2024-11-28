//#include <CGAL/Constrained_Delaunay_triangulation_2.h>
//#include <CGAL/mark_domain_in_triangulation.h>
//#include <CGAL/Polygon_2.h>
//#include <CGAL/draw_triangulation_2.h>
//#include "CGAL-6.0.1/examples/Triangulation_2/polygon_triangulation_graphics_scene_options.h"

#include <iostream>
#include <cstdlib> // For std::atoi


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

void test() {
    Segment s1 = Segment(Point(2,2), Point(3,3));
    Segment s2 = Segment(Point(0,0), Point(1,1));

    std::cout << "intersecting..." << std::endl;
    const auto Ps = CGAL::intersection(s1, s2);
    std::cout << "done" << std::endl;

    if (Ps) {
        if (const Segment* s = std::get_if<Segment>(&*Ps)) {
            std::cout << "Segment: " << s->source() << ", " << s->target() << std::endl;
        } else {
            const Point* p = std::get_if<Point >(&*Ps);
            std::cout << "Point: " << *p << std::endl;
        }
    }
}


Polygon_2 generate_random_polygon(int n, std::optional<int> seed = std::nullopt) {
    Polygon_2 P;
    std::vector<Point> points;
    CGAL::Random rand;
    if (seed.has_value()) {
        rand = CGAL::Random(seed.value());
    }
    std::cout << "Generating random polygon with seed: " << rand.get_seed() << std::endl;

    CGAL::copy_n_unique(Point_generator(1000, rand), n, std::back_inserter(points));
    CGAL::random_polygon_2(points.size(), std::back_inserter(P), points.begin());

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
    std::cout << "Running with " << iterations << " iterations and n = " << n << "." << std::endl;
    for (int k = 0; k < iterations; k++) {
        std::cout << "Iteration: " << k << std::endl;
        // TODO: set seed manually for it to work for small n
        algorithm1(100 * n, polygon_to_arrangement(generate_random_polygon(n))); // seed 4242
    }
//    Polygon needing 3 guards: https://www.desmos.com/geometry/6iocdgnncv
//    std::vector<Point> points = {Point(0,0), Point(5,-1), Point(4,0), Point(8,-2), Point(8,2), Point(4, 1), Point(6, 4),
//                                     Point(10, 2), Point(8, 8), Point(4, 8), Point(6, 10), Point(0, 10), Point(0, 6), Point(8, 6)};
//
//    std::vector<Segment> segments;
//    for (int i = 0; i < points.size(); i++) {
//        segments.emplace_back(points[i], points[(i + 1) % points.size()]);
//    }
//
//    Arrangement_2 A;
//    CGAL::insert_non_intersecting_curves(A,segments.begin(),segments.end());
//
//    algorithm1(T, A);

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

