#include <utility>
#include <string>
#include <hiredis/hiredis.h>

namespace noway{
struct PathfindingRequest{
    int xStart;
    int yStart;
    int xGoal;
    int yGoal;
};

class Redis{
    public:
    Redis(char const* host, const unsigned int port);
    ~Redis();
    int getRequest(PathfindingRequest& request) const;
    

    protected:
    static const std::string REQUEST_KEY;

    redisContext *_ctx;
};
} //namespace noway