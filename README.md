
NoWay
=====

A simple pathfinding module based on the [theta\*](https://en.wikipedia.org/wiki/Theta*) algorithm, communicating thanks to redis.


Installation
------------

1. Install dependencies (a valid c++ toolchain, cmake, pkg-config and hiredis)

 ```bash
sudo apt-get install build-essential cmake pkg-config libhiredis-dev
```

2. Clone and compile 
```bash
git clone https://github.com/rustyducks/NoWay.git 
cd Noway && mkdir build && cd build
cmake ..
make -j8
 ```

Usage
-----
Run the executable : `./NoWay [redis_host] [redis_port]` (default: *127.0.0.1:6379*)
The executable will respond to redis command, here is the common workflow:
1. Update the dynamic obstacles: `RPUSH dynamic_obstacles [xcenter],[ycenter],[radius] ...`
2. Ask a way: `PUBLISH findpath xstart,ystart;xgoal,ygoal`
3. The result will be available on `path`: `GET path` -> `x1,y1;x2,y2;...xn,yn;...xgoal,ygoal;` 

