#include "Algorithm1.h"
#include "Helper.h"

void algorithm1(long T, Arrangement_2 P){
    std::cout << "Algorithm 1 running" << std::endl;

    // get the first edge and point
    Halfedge_circulator e = getEdgesOfArrangement(P)[1];
    Point p = CGAL::midpoint(e->source()->point(), e->target()->point());

    // for-loop over T
    for (int i = 0; i < T; i++){
        auto [guard, p_new, E_new] =  greedyStep(P, e, p);
        p = p_new;
        e = E_new;
        std::cout << "GREEDY STEP " << i << " COMPLETED and ended at point: " << p << " and edge: " <<
        e->source()->point() << " -> " << e->target()->point() << " with guard at: " << guard << std::endl;
    }

}
