#include <cassert>
#include <vector>
#include <map>
#include <queue>

enum Directions {
    IDLE,
    UP,
    DOWN,
};

class Elevator {
public:
    int moveUp() {
        return 1;
    }
    void moveDown() {

    }

private:
    int _currentFloor;
    int _direction;
    
};

class ElevatorController {
public:
    void tick(int ticks = 1) {
        // iterate the system by one.
    }

    void addElevator(int floor = 0) {

    }

    
    void addRequest(int from, int to) {
        Directions direction;
        if (from > to) {
            direction = Directions::DOWN;
        } else {
            direction = Directions::UP;
        }

        
    }
private:
    // elevators
    std::map<int, std::vector<Elevator>> _elevatorsAtFloor;
};

int main() {
    // initialise

    // put in passenger requests
}