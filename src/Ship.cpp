#include "Ship.hpp"

Ship::Ship(int ShipSize)
        :size(ShipSize),
        segments(ShipSize),
        orientation(Orientation::Vertical){
    if(ShipSize  > 4 || ShipSize < 1){
        throw std::invalid_argument("Ship size must be in range[1-4]");
    }
    initSegments();
}


Ship::~Ship() {
    for (auto segment : segments) {
        delete segment; 
    }
}

void Ship::initSegments(){
    segments.resize(size);
    for (int i = 0; i < size; ++i) {
        segments[i] = new ShipSegment(); 
    }
}

std::vector<ShipSegment*> Ship::getSegments() {
    return segments;
}

int Ship::getSize() const{
    return this->size;
}

void Ship::setOrientation(Orientation shipOrientation){
    this->orientation = shipOrientation;
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
