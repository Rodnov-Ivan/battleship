#include "Scanner.hpp"

Scanner::Scanner(GameField& field):field(field){};

void Scanner::useAbility() {
    int x, y;
    std::cout << "Scanner is applying." << std::endl;
    std::cout << "Enter coordinates to scan the area around (x, y):\n";
    std::cin >> x >> y;
    if (x < 0 || x >= field.getWidth() || y < 0 || y >= field.getHeight()){
        throw AbilityError("Error: The coordinates to be scanned are outside the field.");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::vector <std::vector<int>> scannerCoords = {{x, y},
    {x+1, y},{x, y+1},{x+1, y+1}};
    bool flag = false;
    const std::vector<FieldCell>& fieldplayer = field.getField();
    for (std::vector<int> curCoords: scannerCoords){
        if (!((x < 0 || x >= field.getWidth() || y < 0 || y >= field.getHeight()))){
        int index = curCoords[1] * field.getWidth() + curCoords[0];
        if (fieldplayer[index].value == CellValue::ShipSegment) {
            std::cout << "A segment of the ship was found on the site" << std::endl;
            flag = true;
            break;
        }
        }
    }
    if (flag == false) std::cout << "A segment of the ship wasn't found on the site" << std::endl;

}