#include "NoWay/Redis.hpp"

#include <iostream>
#include <sstream>

const std::string noway::Redis::REQUEST_KEY = "findpath";
const std::string noway::Redis::RESPONSE_KEY = "path";
const std::string noway::Redis::DYNAMIC_OBSTACLES_KEY = "dynamic_obstacles";

noway::Redis::Redis(char const* host, const unsigned int port){
    _ctx = redisConnect(host, port);
    _respCtx = redisConnect(host, port);
    if (_ctx == NULL || _ctx->err || _respCtx == NULL || _respCtx->err) {
        if (_ctx) {
            std::cout << "Error when instanciating redis client : " << _ctx->errstr << _respCtx->errstr << std::endl;
            // handle error
        } else {
            std::cout << "Can't allocate redis context" << std::endl;
        }
    }
    redisReply* reply = (redisReply*)redisCommand(_ctx,"SUBSCRIBE %s", REQUEST_KEY.c_str());
    freeReplyObject(reply);
}

noway::Redis::~Redis(){
    redisFree(_ctx);
    redisFree(_respCtx);
}

int noway::Redis::getRequest(noway::PathfindingRequest& request) const{
    redisReply* reply;
    if (redisGetReply(_ctx, (void**)&reply) == REDIS_OK){
        if (reply == nullptr){
            return 0;
        }
        if (reply->elements != 3){  // 0 -> "message", 1 -> key, 2 -> value
            return 0;
        }
        if (reply->element[2]->str == nullptr){
            return 0;
        }
        sscanf(reply->element[2]->str, "%d,%d;%d,%d", &request.xStart, &request.yStart, &request.xGoal, &request.yGoal);
        freeReplyObject(reply);
        return 1;
    }
    return 0;
}

int noway::Redis::sendPath(std::vector<std::pair<int, int>> path) const{
    std::ostringstream os;
    for (auto const &p: path){
        os << p.first << "," << p.second << ";";
    }
    redisAppendCommand(_respCtx, "DEL %s", RESPONSE_KEY.c_str());
    redisAppendCommand(_respCtx, "SET %s %s", RESPONSE_KEY.c_str(), os.str().c_str());
    redisReply* reply;
    redisGetReply(_respCtx,(void**)&reply); // reply for SET
    freeReplyObject(reply);
    redisGetReply(_respCtx,(void**)&reply); // reply for GET
    freeReplyObject(reply);
    return 0;
}

int noway::Redis::getDynamicObstacles(std::vector<noway::CircleObstaclePtr>& obstacles) const{
    obstacles.clear();
    redisReply* reply = (redisReply*)redisCommand(_respCtx, "LRANGE %s 0 -1", DYNAMIC_OBSTACLES_KEY.c_str());
    if ((reply == nullptr) || (reply->type != REDIS_REPLY_ARRAY)){
        return -1;
    }
    for (size_t i=0; i<reply->elements; i++){
        int centerX, centerY;
        double radius;
        sscanf(reply->element[i]->str, "%d,%d,%lf", &centerX, &centerY, &radius);
        obstacles.push_back(std::make_shared<noway::CircleObstacle>(centerX, centerY, radius));
    }

    return reply->elements;
}