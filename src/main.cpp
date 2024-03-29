#include <iostream>
#include <unistd.h>
#include "NoWay/ThetaStar.hpp"
#include "NoWay/PBMReader.hpp"
#include "NoWay/Redis.hpp"



int main(int argc, char** argv) {
    noway::PBMReader pbmr;
    noway::GraphPtr g = std::make_shared<noway::Graph>();
    double graphTableRatio;
    pbmr.readFile("../data/nav_graph.pbm", g, &graphTableRatio);

    noway::ThetaStar ts;
    ts.setGraph({g, graphTableRatio});

    std::string host;
    unsigned int port;
    if (argc == 1){
        host = "127.0.0.1";  // Default host
        port = 6379; // Default port
    }else if (argc == 3){
        host = argv[1];
        sscanf(argv[2], "%ud", &port);
    }else{
        std::cout << "Usage : NoWay [redis_host] [redis_port]" << std::endl;
        return -1;
    }
    
    noway::Redis r(host.c_str(), port);
    noway::PathfindingRequest req;

    while (true){
        if (r.getRequest(req)){
            std::cout << "New pathfinding request received : [" << req.xStart << "," << req.yStart << "] -> [" << req.xGoal << "," << req.yGoal << "]" << std::endl;
            std::vector<noway::CircleObstaclePtr> obstacles;
            int nobs = r.getDynamicObstacles(obstacles);
            ts.resetGraph();
            ts.updateDynamicObstacles(obstacles);
            // ts.displayGraph();
            std::cout << nobs << " obstacles updated" <<std::endl;
            auto t = ts.findPath(req.xStart, req.yStart, req.xGoal, req.yGoal);
            r.sendPath(t);
        }
    }





}
