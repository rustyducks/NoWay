#include <iostream>
#include "ThetaStar.hpp"
#include "PBMReader.hpp"

int main(int, char**) {
    noway::PBMReader pbmr;
    noway::GraphPtr g = std::make_shared<noway::Graph>();
    double graphTableRatio;
    pbmr.readFile("/home/gbuisan/Documents/NoWay/data/nav_graph.pbm", g, &graphTableRatio);


    std::cout << graphTableRatio << std::endl;

    noway::ThetaStar ts;
    ts.setGraph({g, graphTableRatio});
    auto t = ts.findPath(490, 980, 1500, 990);

    for (auto &pt: t){
        std::cout << pt.first << ',' << pt.second << "; ";
    }
    std::cout << std::endl;



}
