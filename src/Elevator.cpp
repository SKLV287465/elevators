#include <cassert>
#include <vector>
#include <map>
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
    int _capacity;
    int _numPassengers;
};

class ElevatorController {
public:
    void tick(int ticks = 1) {
        // iterate the system by one.
    }

    void addElevator(int floor = 0) {

    }

    void add_request(int from, int to) {
        // when i put in a request, i want to find the elevator going the same direction and before the from.
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