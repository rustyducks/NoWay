#include "Redis.hpp"

#include <iostream>

const std::string noway::Redis::REQUEST_KEY = "findpath";

noway::Redis::Redis(char const* host, const unsigned int port){
    _ctx = redisConnect(host, port);
    if (_ctx == NULL || _ctx->err) {
        if (_ctx) {
            std::cout << "Error when instanciating redis client : " << _ctx->errstr << std::endl;
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