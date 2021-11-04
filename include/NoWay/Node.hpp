#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <vector>

namespace noway{
class Node{
public:
    Node(bool occupied, int x, int y);
    double heuristic(const std::shared_ptr<Node> other) const;
    double cost(const std::shared_ptr<Node> other) const;
    bool isFree() const{
        return _free;
    }
    void setFree(bool free=true){
        _free = free;
    }
    int x() const{
        return _x;
    }
    int y() const{
        return _y;
    }
    double h() const{
        return _h;
    }
    void seth(double h) {
        _h = h;
    }
    double g() const{
        return _g;
    }
    void setg(double g){
        _g = g;
    }
    std::shared_ptr<Node> getParent() const{
        return _parent;
    }
    void setParent(std::shared_ptr<Node> parent){
        _parent = parent;
    }
    void reset(){
        seth(0);
        setg(0);
        setFree(_baseValue);
    }
protected:
    double eulerDistance (const std::shared_ptr<Node> other) const;
    double manhattanDistance (const std::shared_ptr<Node> other) const;
    int _x;
    int _y;
    bool _free;
    bool _baseValue;
    double _g;
    double _h;
    std::shared_ptr<Node> _parent;
};
typedef std::shared_ptr<Node> NodePtr;
typedef std::vector<std::vector<NodePtr>> Graph;
typedef std::shared_ptr<Graph> GraphPtr;

struct GraphWithRatio{
    GraphPtr graph;
    double ratio;
};

}

#endif /* NODE_HPP */
