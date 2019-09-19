#include <iostream>
#include "ThetaStar.hpp"
#include "PBMReader.hpp"

int main(int, char**) {
    noway::PBMReader pbmr;
    noway::Graph g;
    pbmr.readFile("/home/gbuisan/Documents/NoWay/data/nav_graph.pbm", &g);
}
