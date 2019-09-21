#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP
#include "Node.hpp"

namespace noway{
class Pathfinder{

public:
virtual std::vector<std::pair<int, int>> findPath(const unsigned int xstart, const unsigned int ystart, const unsigned int xgoal, const unsigned int ygoal) = 0;

};

} // namespace noway
#endif /* PATHFINDER_HPP */
