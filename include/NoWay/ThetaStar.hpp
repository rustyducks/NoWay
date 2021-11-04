#ifndef THETASTAR_HPP
#define THETASTAR_HPP

#include <unordered_set>

#include "NoWay/Node.hpp"
#include "NoWay/Pathfinder.hpp"


namespace noway{
class ThetaStar: public Pathfinder{
    public:
    ThetaStar();

    std::vector<std::pair<int, int>> findPath(const unsigned int xstart, const unsigned int ystart, const unsigned int xgoal, const unsigned int ygoal) override;
    virtual void resetGraph() override;
    virtual void updateDynamicObstacles(std::vector<CircleObstaclePtr> obstacles) override;
    
    void setGraph(GraphWithRatio graph){
        _graph = graph.graph;
        _graphTableRatio = graph.ratio;
    }

    void displayGraph();
    

    protected:
    GraphPtr _graph;
    double _graphTableRatio;
    //std::unordered_set<NodePtr> openedSet;
    std::unordered_set<NodePtr> closed;
    std::vector<NodePtr> opened;

    std::vector<NodePtr> getNeighbours(const NodePtr& node) const;
    void updateNode(const NodePtr& s, NodePtr& s2, const NodePtr& goal);
    bool inLineOfSight(const NodePtr& s, const NodePtr& s2) const;
    std::vector<std::pair<int, int>> reconstructPath(const NodePtr& s) const;


};
} //namespace noway

#endif /* THETASTAR_HPP */
