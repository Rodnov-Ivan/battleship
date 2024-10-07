#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

enum class SegmentStatus {Unbroken, Damaged, Destroyed};

enum class ShipStatus {Unbroken, Damaged, Destroyed};

enum class Orientation {Vertical, Horizontal};

struct Coordinates{
    int x;
    int y;
    bool operator==(const Coordinates &other) const{
        return x == other.x && y == other.y;
    }
};

struct ShipSegment{
    Coordinates coord;
    SegmentStatus status;

    ShipSegment() : coord({ 0, 0 }), status(SegmentStatus::Unbroken) {}
    ShipSegment(Coordinates coord, SegmentStatus status) : coord(coord), status(status) {}
};

#endif STRUCTURES_HPP