#include "GameField.hpp"

GameField::GameField(int fieldHeight, int fieldWidth){
    while(fieldHeight < 1 || fieldWidth < 1){
        std::cout << "Invalid field sizes, write correct sizes" << std::endl;
        std::cin >> fieldHeight >> fieldWidth;
    }
    height = fieldHeight;
    width = fieldWidth;
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

GameField::~GameField() = default;

int GameField::getWidth(){
    return width;
}

int GameField::getHeight(){
    return height;
}

const std::vector<FieldCell>& GameField::getField() const {
    return field;
}

bool GameField::checkFieldBorders(Ship* ship){
    std::vector<ShipSegment*> segments = ship->getSegments();
    for(auto segment : segments){
        int x = segment->coord.x;
        int y = segment->coord.y;
        if(x < 0 || x >= width || y < 0 || y >= height){
            std::cout << "Ship with size " << ship->getSize() << " is out of field, write correct coords" << std::endl; 
            int x; int y;
            std::cin>>x>>y;
            Coordinates segmentCoord = {x, y};
            ship->setCoodrs(segmentCoord);
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
                        std::cout << "Ship with size " << ship->getSize() << " has contact with other on coords,  write correct coords" << x << ", " << y << std::endl; 
                        int x; int y;
                        std::cin>>x>>y;
                        Coordinates segmentCoord = {x, y};
                        ship->setCoodrs(segmentCoord);
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
        std::cout << "Invalid argument: ship is nullptr." << std::endl;
        return;
    }

    if(ship->getIsPlaced()){
        removeShip(ship);
    }
    ship->setOrientation(orientation);
    ship->setCoodrs(coords);
    std::vector<ShipSegment*> segments = ship->getSegments();
    while (checkFieldBorders(ship) == false || checkShipsContact(ship) == false){
        checkFieldBorders(ship);
        checkShipsContact(ship);
    }
    
    for(auto segment : segments){
        int x = segment->coord.x;
        int y = segment->coord.y;
        int index = y * width + x;
        
        field[index].shipSegment = segment;
        field[index].value = CellValue::ShipSegment;
    }
    ship->setIsPlaced(true);
}

void GameField::attackCell(Coordinates coords){
   if (!checkAttackCoord(coords)) {
        std::cout << "Attack coordinate is out of field" << std::endl; 
        return;
    }
    int index = coords.y * width + coords.x;
    FieldCell& cell = field[index];

    if (cell.shipSegment != nullptr) {
        ShipSegment* segment = cell.shipSegment;
        
        if (segment->status == SegmentStatus::Unbroken) {
            segment->status = SegmentStatus::Damaged;
            cell.status = CellStatus::Open;
            std::cout << "Hit! Segment at (" << coords.x << ", " << coords.y << ") is Damaged." << std::endl;
        }
        else if (segment->status == SegmentStatus::Damaged) {
            segment->status = SegmentStatus::Destroyed;
            cell.status = CellStatus::Open;
            std::cout << "Hit! Segment at (" << coords.x << ", " << coords.y << ") is Destroyed." << std::endl;
        }
        else if (segment->status == SegmentStatus::Destroyed) {
            std::cout << "Segment at (" << coords.x << ", " << coords.y << ") is already Destroyed." << std::endl;
        }
    }
    else {
        if (cell.status == CellStatus::Open) {
            std::cout << "Cell (" << coords.x << ", " << coords.y << ") has already been attacked." << std::endl;
        }
        else {
            cell.status = CellStatus::Open;
            cell.value = CellValue::Miss;
            std::cout << "Miss! No ship segment at (" << coords.x << ", " << coords.y << ")." << std::endl;
        }
    }
}

void GameField::removeShip(Ship* ship){
    if(ship == nullptr){
        return;
    }
    const std::vector<ShipSegment*>& segments = ship->getSegments();
    
    for(auto& cell : field){
        if(cell.shipSegment != nullptr){
            for(auto segment : segments){
                if(cell.shipSegment == segment){
                    cell.shipSegment = nullptr;
                    cell.value = CellValue::Empty;
                    break;
                }
            }
        }
    }
    ship->setIsPlaced(false);
}

