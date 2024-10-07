#include "ShipManager.hpp"

ShipManager::ShipManager(std::vector<int> sizes){
    for (int size: sizes){
        Ship* ship = new Ship(size); 
        ships.push_back(ship); 
    }
}

ShipManager::~ShipManager() {
    for (auto& ship : ships) {
        delete ship;  
    }
}

std::vector<Ship*> ShipManager::getAllShips(){
    return ships;
}

Ship* ShipManager::getShipByCoordinates(Coordinates coords){
    for (Ship* ship : ships) {
        std::vector<ShipSegment*> segments = ship->getSegments();
        for (ShipSegment* segment : segments) {
            if (segment->coord == coords) {
                return ship;  
            }
        }
    }
    return nullptr;  
}

void ShipManager::printShipsInfo() {
    for (size_t i = 0; i < ships.size(); ++i) {
        Ship* ship = ships[i];
        std::cout << "Ship " << i + 1 << ": " << std::endl;
        std::cout << "  Size: " << ship->getSize() << std::endl;
        std::cout << "  Orientation: " << (ship->getOrientation() == Orientation::Vertical ? "Vertical" : "Horizontal") << std::endl;

        std::cout << "  Segments: " << std::endl;
        std::vector<ShipSegment*> segments = ship->getSegments();
        for (size_t j = 0; j < segments.size(); ++j) {
            ShipSegment* segment = segments[j];
            std::cout << "    Segment " << j + 1 << " - Coordinates: (" << segment->coord.x << ", " << segment->coord.y << "), Status: ";

            switch (segment->status) {
                case SegmentStatus::Unbroken:
                    std::cout << "Unbroken";
                    break;
                case SegmentStatus::Damaged:
                    std::cout << "Damaged";
                    break;
                case SegmentStatus::Destroyed:
                    std::cout << "Destroyed";
                    break;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
