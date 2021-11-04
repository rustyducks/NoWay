#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP
#include "NoWay/Obstacle.hpp"
#include <vector>

namespace noway{
class Pathfinder{

public:
virtual std::vector<std::pair<int, int>> findPath(const unsigned int xstart, const unsigned int ystart, const unsigned int xgoal, const unsigned int ygoal) = 0;
virtual void resetGraph() = 0;
virtual void updateDynamicObstacles(std::vector<CircleObstaclePtr> obstacles) = 0;

};

} // namespace noway
#endif /* PATHFINDER_HPP */
