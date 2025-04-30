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

    class greaterRequest {
    public:
        bool operator()(Request a, Request b) {
            return a.to < b.to;
        }
    };
    class lesserRequest {
    public:
        bool operator()(Request a, Request b) {
            return b.to < a.to;
        }

    };

    bool compare = [](Request a, Request b) {
        return a.to < b.to;
    }
    std::priority_queue<Request, std::vector<int>, decltype(compare)> _upQueue;
    std::priority_queue<Request, std::vector<int>, std::less<int>> _downQueue;
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
        // find elevators that can take this request on the way

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

    std::map<int, std::vector<Elevator>> _finishLocationElevator;
    std::queue<Request> _queuedElevators;
};

int main() {
    
}

