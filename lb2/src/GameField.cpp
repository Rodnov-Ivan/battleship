#include "GameField.hpp"

GameField::GameField(int fieldHeight, int fieldWidth): orginalAttack(&GameField::averageAttack){
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
        int x = segment->getCoord().x;
        int y = segment->getCoord().y;
        if(x < 0 || x >= width || y < 0 || y >= height){
            return false;
        }
    }
    return true;  
}

bool GameField::checkShipsContact(Ship* ship){
    std::vector<ShipSegment*> segments = ship->getSegments();
    for(auto segment : segments){
        int x = segment->getCoord().x;
        int y = segment->getCoord().y;
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
        std::cout << "Invalid argument: ship is nullptr." << std::endl;
        return;
    }

    if(ship->getIsPlaced()){
        removeShip(ship);
    }
    ship->setOrientation(orientation);
    ship->setCoodrs(coords);
    std::vector<ShipSegment*> segments = ship->getSegments();
    if(checkFieldBorders(ship) == false){
        throw PlaceShipError("Error: Ship cannot be placed out of field.");
    };
    if (checkShipsContact(ship) == false){
        throw PlaceShipError("Error: Ship has contact with other on coords");
    }
    
    for(auto segment : segments){
        int x = segment->getCoord().x;
        int y = segment->getCoord().y;
        int index = y * width + x;
        field[index].ship = ship;
        field[index].shipSegment = segment;
        field[index].value = CellValue::ShipSegment;
    }
    ship->setIsPlaced(true);
}

bool GameField::attackCell(Coordinates coords){
   if (!checkAttackCoord(coords)) {
         throw AttackError("The coordinates for the attack are outside the field.");
        return false;
    }
    int index = coords.y * width + coords.x;
    FieldCell& cell = field[index];
    cell.status = CellStatus::Open;
    switch (cell.value) {
        case CellValue::Empty:
            cell.value = CellValue::Miss;
            std::cout << "Missed at (" << coords.x << ", " << coords.y << ")\n";
            break;

        case CellValue::Miss:
            std::cout << "Was attacked (" << coords.x << ", " << coords.y << ")\n";
            break;

        case CellValue::ShipSegment:
            switch (cell.shipSegment->getStatus()) {
                    case SegmentStatus::Unbroken:
                        std::cout << "The ship is damaged at (" << coords.x << ", " << coords.y << ")!\n";
                        break;
                    case SegmentStatus::Damaged:
                        std::cout << "The segment of the ship at (" << coords.x << ", " << coords.y << ") is destroyed!\n";
                        break;
                    case SegmentStatus::Destroyed:
                        std::cout << "The segment of the ship at (" << coords.x << ", " << coords.y << ") was already destroyed!\n";
                        return false;
                        break;
                    default:
                        break;
                }
            (this->*orginalAttack)(cell.shipSegment);
            if (cell.ship->getIsDestroyed() == true) std::cout << "The ship is destroyed!\n";
            return cell.ship->getIsDestroyed();
            break; 

        default:
            break;
    }
    return false;
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

void GameField::setDoubleDamage() {
    orginalAttack = &GameField::doubleDamageAttack;
}

void GameField::doubleDamageAttack(ShipSegment* shipSegment) {
    if (shipSegment->getStatus() != SegmentStatus::Destroyed){
        std::cout << "Double Damage attack was performed. " << std::endl;
        shipSegment->setStatus(SegmentStatus::Destroyed);
        std::cout << "This segment of the ship is destroyed!\n";
    }
    orginalAttack = &GameField::averageAttack;
   
}

void GameField::averageAttack(ShipSegment* shipSegment) {
    shipSegment->takeDamage();
}