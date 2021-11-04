#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <memory>

namespace noway{

struct CircleObstacle{
    int centerX;
    int centerY;
    double radius;

    CircleObstacle(int cX, int cY, double r): centerX(cX), centerY(cY), radius(r){
    }
};

typedef std::shared_ptr<CircleObstacle> CircleObstaclePtr;

} // namespace noway
#endif /* OBSTACLE_HPP */
