#include "Ship.hpp"

Ship::Ship(int ShipSize)
        :size(ShipSize),
        segments(ShipSize),
        orientation(Orientation::Vertical){
    if(ShipSize  > 4 || ShipSize < 1){
        throw std::invalid_argument("Ship size must be in range[1-4]");
    }
}

Ship::~Ship() {
    for (auto segment : segments) {
        delete segment; 
    }
}

std::vector<ShipSegment*> Ship::getSegments() {
    return segments;
}

int Ship::getSize() const{
    return this->size;
}

void Ship::changeOrientation(){
    this->orientation = (orientation == Orientation::Vertical ? Orientation::Horizontal : Orientation::Vertical);
}

Orientation Ship::getOrientation() const{
    return this->orientation;
}

void Ship::setCoodrs(Coordinates coords){
    std::vector<ShipSegment*> segments = this->getSegments();
    for (int i = 0; i < size; ++i) {
        if (orientation == Orientation::Vertical) {
            segments[i]->coord = {coords.x, coords.y+i};
        } else {
            segments[i]->coord = {coords.x+i, coords.y};
        }
    }
}
