#include "ThetaStar.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include "TableParams.hpp"


noway::ThetaStar::ThetaStar(){

}

std::vector<std::pair<int, int>> noway::ThetaStar::findPath(const unsigned int xstart, const unsigned int ystart, const unsigned int xgoal, const unsigned int ygoal){
    std::cout << "graph size : " << _graph->size() << (*_graph)[0].size() << std::endl;
    
    NodePtr startNode = (*_graph)[std::floor(xstart * _graphTableRatio)][std::floor(ystart * _graphTableRatio)];
    NodePtr goalNode = (*_graph)[std::floor(xgoal * _graphTableRatio)][std::floor(ygoal * _graphTableRatio)];

    std::cout << "start node : " << startNode->x() << ";" << startNode->y() << ":" << startNode->isFree() << std::endl;
    std::cout << "goal node : " << goalNode->x() << ";" << goalNode->y() << goalNode->isFree() << std::endl;

    opened.clear();
    //openedSet.clear();
    closed.clear();
    
    if (!startNode->isFree()){
        std::cout << "Start node is not free, aborting." <<std::endl;
        return {};
    }
    if (!goalNode->isFree()){
        std::cout << "Goal node is not free, aborting." << std::endl;
        return {};
    }
    startNode->seth(startNode->heuristic(goalNode));
    opened.push_back(startNode);
    push_heap(opened.begin(), opened.end(), HeapCompare_f());
    while (!opened.empty()){
        NodePtr current;
        current = opened.front();
        pop_heap(opened.begin(), opened.end(), HeapCompare_f());
        opened.pop_back();
        if (current == goalNode){
            //Path found
            std::cout << "Path found" << std::endl;
            return reconstructPath(current);
        }
        closed.insert(current);
        for (auto s2: getNeighbours(current)){
            if (closed.find(s2) == closed.end()){
                if (std::find(opened.begin(), opened.end(), s2) == opened.end()){
                    s2->setg(INFINITY);
                    s2->setParent(nullptr);
                }
                updateNode(current, s2, goalNode);
            }
        }
    }
    std::cout << "No path found" << std::endl;
    return std::vector<std::pair<int, int>>();
}

std::vector<std::pair<int, int>> noway::ThetaStar::reconstructPath(const NodePtr& s) const{
    std::vector<std::pair<int, int>> path;
    NodePtr sPath = s;
    while(sPath->getParent() != nullptr){
        path.emplace_back(sPath->x() / _graphTableRatio, sPath->y() / _graphTableRatio);
        sPath = sPath->getParent();
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<noway::NodePtr> noway::ThetaStar::getNeighbours(const NodePtr& node) const{
    std::vector<noway::NodePtr> neighbours;
    if ((node->x() > 0) && ((*_graph)[node->x() - 1][node->y()]->isFree())){
        neighbours.push_back((*_graph)[node->x() - 1][node->y()]);
    }
    if ((node->x() < (int)_graph->size() - 1) && ((*_graph)[node->x() + 1][node->y()]->isFree())){
        neighbours.push_back((*_graph)[node->x() + 1][node->y()]);
    }
    if ((node->y() > 0) && ((*_graph)[node->x()][node->y() - 1]->isFree())){
        neighbours.push_back((*_graph)[node->x()][node->y() - 1]);
    }
    if ((node->y() < (int)_graph->at(node->x()).size() - 1) && ((*_graph)[node->x()][node->y() + 1]->isFree())){
        neighbours.push_back(_graph->at(node->x()).at(node->y() + 1));
    }
    return neighbours;
}

void noway::ThetaStar::updateNode(const noway::NodePtr& s, noway::NodePtr& s2, const noway::NodePtr& goal){
    if (s->getParent() != nullptr && inLineOfSight(s->getParent(), s2)){
        double cost = s->getParent()->g() + s->getParent()->cost(s2);
        if (cost < s2->g()){
            s2->setg(cost);
            s2->setParent(s->getParent());
        }
        auto item = std::find(opened.begin(), opened.end(), s2);
        if (item != opened.end()){
            opened.erase(item);
            make_heap(opened.begin(), opened.end(), HeapCompare_f());
        }
        s2->seth(s2->heuristic(goal));
        opened.push_back(s2);
        push_heap(opened.begin(), opened.end(), HeapCompare_f());
    }else{
        double cost = s->g() + s->cost(s2);
        if (cost < s2->g()){
            s2->setg(cost);
            s2->setParent(s);
            auto item = std::find(opened.begin(), opened.end(), s2);
            if (item != opened.end()){
                opened.erase(item);
                make_heap(opened.begin(), opened.end(), HeapCompare_f());
            }
            s2->seth(s2->heuristic(goal));
            opened.push_back(s2);
            push_heap(opened.begin(), opened.end(), HeapCompare_f());
        }
    }
}

bool noway::ThetaStar::inLineOfSight(const NodePtr& s, const NodePtr& s2) const{
    int x0 = s->x(), y0 = s->y(), x1 = s2->x(), y1 = s2->y();
    int dx = x1 - x0, dy = y1 - y0;
    int f = 0, sy = 1, sx = 1;
    if (dy < 0){
        dy = -dy;
        sy = -1;
    }
    if (dx < 0){
        dx = -dx;
        sx = -1;
    }
    if (dx >= dy){
        while (x0 != x1){
            f = f + dy;
            if (f >= dx){
                if (!((*_graph)[x0 + (sx - 1) / 2][y0 + (sy - 1) / 2]->isFree())){
                    return false;
                }
                y0 = y0 + sy;
                f = f - dx;
            }
            if ((f != 0) && (!((*_graph)[x0 + (sx - 1) / 2][y0 + (sy - 1) / 2]->isFree()))){
                return false;
            }
            if ((dy == 0) && (!((*_graph)[x0 + (sx - 1) / 2][y0]->isFree())) && (!((*_graph)[x0 + (sx - 1) / 2][y0 - 1]->isFree()))){
                return false;
            }
            x0 = x0 + sx;
        }
    }else{
        while (y0 != y1){
            f = f + dx;
            if (f >= dy){
                if (!((*_graph)[x0 + (sx - 1) / 2][y0 + (sy - 1) / 2]->isFree())){
                    return false;
                }
                x0  = x0 + sx;
                f = f - dy;
            }
            if ((f != 0) && (!((*_graph)[x0 + (sx - 1) / 2][y0 + (sy - 1) / 2]->isFree()))){
                return false;
            }
            if ((dx == 0) && (!((*_graph)[x0][y0 + (sy - 1) / 2]->isFree())) && (!((*_graph)[x0 - 1][y0 + (sy - 1) / 2]->isFree()))){
                return false;
            }
            y0 = y0 + sy;
        }
    }
    return true;
}

