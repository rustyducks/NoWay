#include <iostream>
#include <unistd.h>
#include "ThetaStar.hpp"
#include "PBMReader.hpp"
#include "Redis.hpp"



int main(int argc, char** argv) {
    noway::PBMReader pbmr;
    noway::GraphPtr g = std::make_shared<noway::Graph>();
    double graphTableRatio;
    pbmr.readFile("/home/gbuisan/Documents/NoWay/data/nav_graph.pbm", g, &graphTableRatio);

    noway::ThetaStar ts;
    ts.setGraph({g, graphTableRatio});

    std::string host;
    unsigned int port;
    if (argc == 1){
        host = "127.0.0.1";  // Default host
        port = 6379; // Default port
    }else if (argc == 3){
        host = argv[1];
        sscanf(argv[2], "%d", &port);
    }else{
        std::cout << "Usage : NoWay [redis_host] [redis_port]" << std::endl;
        return -1;
    }
    
    noway::Redis r(host.c_str(), port);
    noway::PathfindingRequest req;

    while (true){
        if (r.getRequest(req)){
            std::cout << "New pathfinding request received : [" << req.xStart << "," << req.yStart << "] -> [" << req.xGoal << "," << req.yGoal << "]" << std::endl;
            auto t = ts.findPath(req.xStart, req.yStart, req.xGoal, req.yGoal);
        }
    }





}
