#include <cassert>

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

int main() {
    
}