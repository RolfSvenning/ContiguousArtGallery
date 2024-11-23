#include "Helper.h"


void printPolygonEdges(const Polygon& P, const std::string& name) {
    std::cout << name << " edges:" << std::endl;
    for (auto eit = P.edges_begin(); eit != P.edges_end(); ++eit)
        std::cout << "[" << eit->source()->point() << " -> " << eit->target()->point() << "] ";
    std::cout << std::endl;
}