#include "NoWay/Node.hpp"
#include <cmath>

using namespace noway;
Node::Node(bool free, int x, int y): _x(x), _y(y), _free(free), _baseValue(free), _g(0), _h(0), _parent(nullptr){

}

double Node::Node::heuristic(const std::shared_ptr<Node> other) const{
    return manhattanDistance(other);
}

double Node::Node::cost(const std::shared_ptr<Node> other) const{
    return eulerDistance(other);
}

double Node::Node::manhattanDistance(const NodePtr other) const{
    return std::abs(_x - other->x()) + std::abs(_y - other->y());
}

double Node::Node::eulerDistance(const NodePtr other) const{
    return std::sqrt(std::pow(_x - other->x(), 2) + (std::pow(_y - other->y(), 2)));
}