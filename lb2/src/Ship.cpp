#include "Ship.hpp"

Ship::Ship(int shipLength)
    : size(shipLength), isPlaced(false), isDestroyed(false){
    segments.resize(shipLength);
    for (int i = 0; i < shipLength; ++i) {
        segments[i] = new ShipSegment(); 
    }
}

Ship::~Ship() {
    for (auto segment : segments) {
        delete segment; 
    }
}


std::vector<ShipSegment*>& Ship::getSegments() {
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
    for (int i = 0; i < size; ++i) {
        if (orientation == Orientation::Vertical) {
            segments[i]->setCoord(coords.x, coords.y+i);
        } else {
            segments[i]->setCoord(coords.x+i, coords.y);
        }
    }
}

bool Ship::getIsPlaced() const {
    return isPlaced;
}

void Ship::setIsPlaced(bool placed){
    isPlaced = placed;
}

void Ship::setStatus(bool status){
    isDestroyed = status;
}

bool Ship::getIsDestroyed(){
    for (int i = 0; i < size; ++i) {
        if (segments[i] != nullptr && 
            (segments[i]->getStatus() == SegmentStatus::Unbroken || 
             segments[i]->getStatus() == SegmentStatus::Damaged)) {
            return false;
        }
    }
    return true;
}
