#include <utility>
#include <string>
#include <vector>
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
    int sendPath(std::vector<std::pair<int, int>> path) const;
    

    protected:
    static const std::string REQUEST_KEY;
    static const std::string RESPONSE_KEY;

    redisContext *_ctx;
    redisContext *_respCtx;
};
} //namespace noway