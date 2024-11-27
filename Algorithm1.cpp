#include "Algorithm1.h"
#include "Helper.h"



bool isInGeneralPosition(const std::vector<Point>& Ps) {
    // Check all triplets of points
    for (size_t i = 0; i < Ps.size(); ++i) {
        for (size_t j = i + 1; j < Ps.size(); ++j) {
            for (size_t k = j + 1; k < Ps.size(); ++k) {
                if (CGAL::collinear(Ps[i], Ps[j], Ps[k])) {
                    return false; // Found a collinear triplet
                }
            }
        }
    }
    return true; // No collinear triplets found
}


void algorithm1(long T, Arrangement_2 P){
    std::cout << "Algorithm 1 running" << std::endl;

    // get the first edge and point
    Halfedge_circulator e = getEdgesOfArrangement(P)[1];
    Point p = CGAL::midpoint(e->source()->point(), e->target()->point());
    std::set<Point> S;
    S.insert(p);

    // for-loop over T
    for (int i = 0; i < T; i++){
        auto [guard, p_new, E_new] =  greedyStep(P, e, p);
        p = p_new;
        e = E_new;
        std::cout << "GREEDY STEP " << i << " COMPLETED and ended at point: " << p << " and edge: " <<
        e->source()->point() << " -> " << e->target()->point() << " with guard at: " << guard << std::endl;
        // if p in S then do one final round until you p again
        if (S.contains(p)){
            std::cout << "Found repetition with point p: " << p << " after i =" << i << " greedy steps" << std::endl;
            break;
        }
        S.insert(p);
    }

//    do {
//        auto [guard, p_new, E_new] =  greedyStep(P, e, p);
//        p = p_new;
//        e = E_new;
//        e->source()->point() << " -> " << e->target()->point() << " with guard at: " << guard << std::endl;
//        // if p in S then do one final round until you p again
//        if (S.contains(p)){
//            std::cout << "Found repetition with point p: " << p << " after i =" << i << " greedy steps" << std::endl;
//            break;
//        }
//        S.insert(p);
//    } while (true);



}
