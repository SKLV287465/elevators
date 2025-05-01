/*
These are elevators that prioritise requests that have been placed first
people who place request first are prioritised over the next requests
*/
#include <map>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>

enum Direction {
    UP,
    DOWN,
    IDLE
};

class Elevator {
private:
    std::unordered_multimap<int, Request> _destinations;
    int _floor;

    struct HighToLow {
        bool operator()(Request a, Request b) {
            return a.to > b.to;
        }
    };
    struct LowToHigh {
        bool operator()(Request a, Request b) {
            return a.to < b.to;
        }
    };

    std::priority_queue<Request, std::vector<int>, HighToLow> _upQueue;
    std::priority_queue<Request, std::vector<int>, LowToHigh> _downQueue;
};

class Request {
public:
    Request(int to, int from) : to(to), from(from) {
        if (to > from) {
            direction = UP;
        } else {
            direction = DOWN;
        }
    }
    int const to;
    int const from;
    Direction direction;
};

class ElevatorController {
public:
    void addRequest(Request request) {
        Direction requestDirection;
        if (request.to < request.from) {
            requestDirection = DOWN;
        } else {
            requestDirection = UP;
        }
        // find elevators that can take this request on the way
        if (requestDirection == UP) {
            // look at elevators below this

        } else if (requestDirection == DOWN) {
            // look at elevators above this
        }
        // find elevator that can finish their requests 
        // then get to this request first

        // add 
    }

private:
    bool _findOnTheWay(Request request) {
        return false;
    }

    void _findFastest(Request request) {

    }
    int levels;
    std::multimap<int, Elevator>  _finishLocationElevator;
    std::queue<Request> _queuedRequests;
};

int main() {
    
}

