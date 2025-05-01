#include <queue>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <optional>
#include <iostream>
#include <string>
enum Direction {
    IDLE,
    UP,
    DOWN,
};

int counter = 0;

/**
 * preconditions:
 * to and from must be distinct
 */
class Request {
    public: 
        Request(int to, int from) : to(to), from(from) {
            if (to > from) {
                direction = UP;
            } else {
                direction = DOWN;
            }
        }
        int to;
        int from;
        Direction direction;

        std::string const toString() const {
            auto ret = std::string{};
            ret.append("to: ");
            ret.append(std::to_string(to));
            ret.append(" from: ");
            ret.append(std::to_string(from));
            return ret;
        }
    };

class Elevator {
public:
    Elevator() {
        direction = IDLE;
        floor = 0;
        _upQueue = std::priority_queue<Request, std::vector<Request>, HighToLow>{};
        _downQueue = std::priority_queue<Request, std::vector<Request>, LowToHigh>{};
        pickup = false;
        id = counter;
        ++counter;
    }

    Direction direction;
    int floor;
    int id;
    void doTicks(int ticks = 1) {
        for (auto i = 0; i < ticks + 1; ++i) {
            tick();
        }
    }

    bool operator<(const Elevator& other) const {
        // Define the criteria for comparison (e.g., based on destinationFloor)
        return this->floor < other.floor;
    }

    void tick() {
        if (direction == UP) {
            floor += 1;
        } else {
            floor -= 1;
        }
        // moves the elevator tick amount
        // can move 1 floor every tick.
        if (_upQueue.empty() && _downQueue.empty()) {
            if (isAvailable()) return;
            auto req = pickupRequest.value();
            if (req.from == floor) {
                pickup = false;
                _addRequestToQueue(req);
            }
        } else {
            if (direction == UP) {
                auto changed = true;
                while (changed) {
                    changed = false;
                    auto closest = _upQueue.top();
                    if (closest.to == floor) {
                        _upQueue.pop(); // request leaves
                        std::cout << "request from " << closest.from << " to " << closest.to << " delivered!" << std::endl;
                        changed = true;
                    }
    
                }
            } else {
                auto changed = true;
                while (changed) {
                    changed = false;
                    auto closest = _downQueue.top();
                    if (closest.to == floor) {
                        _downQueue.pop(); // request leaves
                        std::cout << "request from " << closest.from << " to " << closest.to << " delivered!" << std::endl;
                        changed = true;
                    }
    
                }
            }
        }

        
    }
    void addRequest(Request const& req) {
        // somewhat hard part.
        // if elevator is already moving, i need to just add to queue
        std::cout << req.toString() << " elevator: " << id << std::endl;
        if (direction == IDLE) {
            if (floor == req.from) {
                _addRequestToQueue(req);
            } else {
                pickup = true;
                pickupRequest = req;
                // change direction towards req.from
                if (req.from < floor) {
                    direction = DOWN;
                } else {
                    direction = UP;
                }
            }
        } else {
            _addRequestToQueue(req);
        }
        // if elevator is IDLE i need to add to queue and make it start moving.
        // edge case of 
    }

    bool isAvailable() {
        return !pickup;
    }
private:
    void _addRequestToQueue(Request const& req) {
        if (req.direction == UP) {
            direction = UP;
            _upQueue.push(req);
        } else {
            direction = DOWN;
            _downQueue.push(req);
        }   
    }
    struct HighToLow {
        bool operator()(Request a, Request b) {
            return a.to < b.to; // is this correct?
        }
    };
    struct LowToHigh {
        bool operator()(Request a, Request b) {
            return b.to < a.to; // is this correct?
        }
    };
    bool pickup;
    std::optional<Request> pickupRequest;
    std::priority_queue<Request, std::vector<Request>, HighToLow> _upQueue;
    std::priority_queue<Request, std::vector<Request>, LowToHigh> _downQueue;
};

class ElevatorController {
public:
    ElevatorController(int numElevators) {
        for (auto i = 0; i < numElevators; ++i) {
            _Elevators.emplace_back(Elevator());
        }
    };

    void doTicks(int ticks) {
        for (auto& elevator : _Elevators) {
            elevator.doTicks(ticks);
        }
    }

    void addRequest(Request const& req) {
        // look for elevators that can take request on the way
        if (_onTheWayRequest(req)) return;
        // look for closest idle elevators
        if (_closestIdleRequest(req)) return;
        // add to queue otherwise
        _queuedRequests.push(req);
    }

    void tick(int ticks = 1) {
        // passes time.
    }
private:
    std::queue<Request> _queuedRequests;
    std::vector<Elevator> _Elevators;
    /**
     * returns true if elevator matched to request
     */
    bool _onTheWayRequest(Request const& req) {
        auto candidates = std::vector<Elevator>{};
        for (auto& elevator : _Elevators) {
            if (!elevator.isAvailable()) continue;
            if (req.direction == UP) {
                if (elevator.floor < req.from && elevator.direction == UP) {
                    candidates.push_back(elevator);
                }
            } else {
                if (elevator.floor > req.from && elevator.direction == DOWN) {
                    candidates.push_back(elevator);
                }
            }
        }

        if (candidates.empty()) return false;

        // sort
        std::sort(candidates.begin(), candidates.end());
        if (req.direction == UP) {
            // find highest one
            candidates[candidates.size() - 1].addRequest(req);
        } else {
            candidates[0].addRequest(req);
        }
        return true;
    }
    bool _closestIdleRequest(Request const& req) {
        auto candidates = std::vector<std::pair<int, Elevator>>{};
        for (auto& elevator : _Elevators) {
            if (!elevator.isAvailable()) continue;
            if (elevator.direction == IDLE) {
                candidates.push_back({std::abs(req.from - elevator.floor), elevator});
            }
        }

        // find the nearest one
        if (candidates.empty()) return false;
        std::sort(candidates.begin(), candidates.end());
        candidates[0].second.addRequest(req);
        return true;
    }
};



int main() {
    auto controller = ElevatorController(5);
    auto req1 = Request(10, 1);
    auto req2 = Request(1, 10);
    controller.addRequest(req1);
    controller.addRequest(req2);
    controller.doTicks(20);
}