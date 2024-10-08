#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

enum class SegmentStatus {Unbroken, Damaged, Destroyed};

enum class Orientation {Vertical, Horizontal};

enum class CellStatus {Closed, Open};

enum class CellValue {Empty, Miss, ShipSegment};

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

struct FieldCell{
    CellValue value;
    CellStatus status;
    Coordinates coord;
    ShipSegment* shipSegment;
    FieldCell(Coordinates coords) : value(CellValue::Empty), status(CellStatus::Closed), coord(coords), shipSegment(nullptr){}

};

#endif // STRUCTURES_HPP