#ifndef SHIPSEGMENT_HPP
#define SHIPSEGMENT_HPP
#include "Structures.hpp"


enum class SegmentStatus { Unbroken, Damaged, Destroyed };

class ShipSegment{
private:
    SegmentStatus hp;
    Coordinates coords;
public:
    ShipSegment();
    ~ShipSegment();
    void setCoord(int x, int y);
    void setStatus(SegmentStatus status);
    Coordinates getCoord();
    void takeDamage();
    SegmentStatus getStatus();
};

#endif //SHIPSEGMENT_HPP
