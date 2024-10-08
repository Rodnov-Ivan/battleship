#include "GameField.hpp"

GameField::GameField(int fieldHeight, int fieldWidth)
    : height(fieldHeight), width(fieldWidth){
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            field.push_back(FieldCell(Coordinates{x, y}));
        }
    }
}

GameField::GameField(const GameField& other) 
    : height(other.height), width(other.width), field(other.field) {}

GameField::GameField(GameField&& other)
	: height(other.height), width(other.width), field(std::move(other.field)) {
	other.width = 0;
	other.height = 0;
	other.field.clear();
}

GameField& GameField::operator=(const GameField& other){
    if (this != &other) {
		width = other.width;
		height = other.height;
		field = other.field;
    }
	return *this;
}

GameField& GameField::operator=(GameField&& other) {
	if (this != &other) {
		width = other.width;
		height = other.height;
		field = std::move(other.field);
		other.width = 0;
		other.height = 0;
	}
	return *this;
}

bool GameField::checkFieldBorders(Ship* ship){
    std::vector<ShipSegment*> segments = ship->getSegments();
    for(auto segment : segments){
        int x = segment->coord.x;
        int y = segment->coord.y;
        if(x < 0 || x >= width || y < 0 || y >= height){
            return false;
        }
    }
    return true;  
}

bool GameField::checkShipsContact(Ship* ship){
    std::vector<ShipSegment*> segments = ship->getSegments();
    for(auto segment : segments){
        int x = segment->coord.x;
        int y = segment->coord.y;
        for(int dx = -1; dx <= 1; ++dx){
            for(int dy = -1; dy <= 1; ++dy){
                int nx = x + dx;
                int ny = y + dy;
                if(nx >= 0 && nx < width && ny >= 0 && ny < height){
                    int index = ny * width + nx;
                    FieldCell &cell = field[index];
                    if(cell.shipSegment != nullptr){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool GameField::checkAttackCoord(Coordinates coord){
    int x = coord.x;
    int y = coord.y;
    if(x < 0 || x >= width || y < 0 || y >= height){
        return false;
    }
    return true;
}

void GameField::placeShip(Ship* ship, Coordinates coords, Orientation orientation){
    if(ship == nullptr){
        throw std::invalid_argument("Invalid argument: ship is nullptr.");
    }
    int lenght = ship->getSize();
    ship->setOrientation(orientation);
    ship->setCoodrs(coords);
    std::vector<ShipSegment*> segments = ship->getSegments();
    if(!checkFieldBorders(ship)){
        throw std::out_of_range("Ship is out of field"); 
    }
    if(!checkShipsContact(ship)){
        throw std::runtime_error("Ship has contact with other");
    }
    for(auto segment : segments){
        int x = segment->coord.x;
        int y = segment->coord.y;
        int index = y * width + x;
        
        field[index].shipSegment = segment;
        field[index].value = CellValue::ShipSegment;
    }
}

void GameField::attackCell(Coordinates coords){
   if (!checkAttackCoord(coords)) {
        throw std::out_of_range("Attack coordinate is out of field");
    }
    int index = coords.y * width + coords.x;
    FieldCell& cell = field[index];

    if (cell.status == CellStatus::Open) {
        std::cout << "Cell (" << coords.x << ", " << coords.y << ") has already been attacked." << std::endl;
        return;
    }

    cell.status = CellStatus::Open;

    if (cell.shipSegment != nullptr) {
        ShipSegment* segment = cell.shipSegment;

        if (segment->status == SegmentStatus::Unbroken) {
            segment->status = SegmentStatus::Damaged;
            std::cout << "Hit! Segment at (" << coords.x << ", " << coords.y << ") is Damaged." << std::endl;
        } else if (segment->status == SegmentStatus::Damaged) {
            segment->status = SegmentStatus::Destroyed;
            std::cout << "Hit! Segment at (" << coords.x << ", " << coords.y << ") is Destroyed." << std::endl;
        }
    } else {
        cell.value = CellValue::Miss;
        std::cout << "Miss! No ship segment at (" << coords.x << ", " << coords.y << ")." << std::endl;
    }
}

