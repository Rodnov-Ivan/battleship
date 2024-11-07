#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP


enum class Orientation { Vertical, Horizontal };

enum class CellStatus { Closed, Open };

enum class CellValue { Empty, Miss, ShipSegment };





struct Coordinates {
    int x;
    int y;
    bool operator==(const Coordinates &other) const {
        return x == other.x && y == other.y;
    }
};

class Ship;
class ShipSegment;

struct FieldCell {
    CellValue value;
    CellStatus status;
    Coordinates coord;
    ShipSegment* shipSegment = nullptr;
    Ship* ship = nullptr;

    FieldCell(Coordinates coords)
        : value(CellValue::Empty), status(CellStatus::Closed), coord(coords), shipSegment(nullptr), ship(nullptr) {}
};

#endif // STRUCTURES_HPP
