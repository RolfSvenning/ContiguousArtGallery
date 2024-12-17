//// Copyright (c) 2024 Rolf Svenning
////
//// Permission is hereby granted, free of charge, to any person obtaining a
//// copy of this software and associated documentation files (the
//// "Software"), to deal in the Software without restriction, including
//// without limitation the rights (to use, copy, modify, merge, publish,
//// distribute, sublicense, and/or sell copies of the Software, and to
//// permit persons to whom the Software is furnished to do so, subject to
//// the following conditions:
////
//// The above copyright notice and this permission notice shall be included
//// in all copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
//// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "Algorithm1.h"
#include "Helper.h"
//#include <CGAL/draw_arrangement_2.h>

void algorithm1(long T, const Arrangement_2& A){
    // Choose arbitrary starting point x_0
    Halfedge_circulator e = getEdgesOfArrangement(A)[1];
    Point p = e -> target() -> point();
    Point pStart = p;
    std::set<Point> S;
    S.insert(p);
    Point repetitionPoint;
    int i, j;

    std::vector<Point> Gs;
    std::vector<Point> Ps;
    std::vector<std::vector<Point>> VPs;

    // for-loop over T
    for (i = 0; i < T; i++){
        auto [guard, e_new, p_new, isFinished] =  greedyInterval(A, e, p);
        Gs.emplace_back(guard);
        Ps.emplace_back(p);
        Ps.emplace_back(p_new);
        p = p_new;
        e = e_new;
        VPs.emplace_back(getVerticesOfArrangement(computeVisibilityArrangementGeneral(A, guard)));

        if (isFinished) {
            writeOutput("../outputs.txt", i, 0, A, Gs, Ps, VPs, pStart, true); // < --- THIS LINE WRITES OUTPUT TO FILE
//            CGAL::draw(A); // needs #include <CGAL/draw_arrangement_2.h>
            return;
        }

        // if p in S then do one final round to find an optimal solution
        if (S.contains(p)){
            repetitionPoint = p;
            break;
        }
        S.insert(p);
    }

    // starting from an optimal endpoint (repetitionPoint), perform one revolution around the polygon to find an optimal solution
    for (j = 0; j < A.number_of_vertices(); j++) {
        std::optional<Point> start = (j != 0 ? std::optional<Point>(repetitionPoint) : std::nullopt);
        auto [guard, e_new, p_new, isFinished] =  greedyInterval(A, e, p, start);

        Gs.emplace_back(guard);
        Ps.emplace_back(p);
        Ps.emplace_back(p_new);
        p = p_new;
        e = e_new;
        VPs.emplace_back(getVerticesOfArrangement(computeVisibilityArrangementGeneral(A, guard)));

        if (isFinished) {
            break;
        }
    }

    writeOutput("../outputs.txt", i, j, A, Gs, Ps, VPs, pStart, true); // < --- THIS LINE WRITES OUTPUT TO FILE
//    CGAL::draw(A); // needs #include <CGAL/draw_arrangement_2.h>
}




