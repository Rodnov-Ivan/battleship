
#include "ShipSegment.hpp"

ShipSegment::ShipSegment():hp(SegmentStatus::Unbroken), coords({0,0}){}

ShipSegment::~ShipSegment() = default;

void ShipSegment::takeDamage(){
    switch (hp) {
        case SegmentStatus::Unbroken:
            hp = SegmentStatus::Damaged;
            break;

        case SegmentStatus::Damaged:
            hp = SegmentStatus::Destroyed;
            break;

        case SegmentStatus::Destroyed:
            break;

        default:
            break;
        }
}

void ShipSegment::setCoord(int x, int y){
    coords = {x, y};
}

Coordinates ShipSegment::getCoord(){
    return coords;
}

SegmentStatus ShipSegment::getStatus(){
    return hp;
}

void ShipSegment::setStatus(SegmentStatus status){
    hp = status;
}