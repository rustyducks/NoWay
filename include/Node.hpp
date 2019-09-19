#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <vector>

namespace noway{
class Node{
public:
    Node(bool occupied, int x, int y);
    double heuristic(Node other);
    double cost(Node other);
    bool isFree();
    void setFree(bool free=true);
    int x();
    int y();
    int h();
    int g();
protected:
    double eulerDistance (Node other);
    double manhattanDistance (Node other);
    bool _free;
    bool _baseValue;
    int _x;
    int _y;
    int _h;
    int _g;
    Node* parent;
};
typedef std::shared_ptr<Node> NodePtr;
typedef std::vector<std::vector<NodePtr>> Graph;
}

#endif /* NODE_HPP */
