#include "GameField.hpp"
#include "ShipManager.hpp"
#include "FieldDrawer.hpp"
#include "AbilityManager.hpp"
#include "Ship.hpp"
#include <vector>
#include "Structures.hpp"
#include <sstream>
#include <string>
#include <iostream>

int main(){
    std::vector<int> sizes = {1, 1, 2, 2, 3, 3, 4};
    
    ShipManager manager(sizes);
    GameField field(10, 10);
    FieldDrawer drawer;
    AbilityManager abilityManager(field);
    std::vector<Ship*> ships = manager.getAllShips();


    for (const auto& ship : ships) {
        bool placed = false;
        while (!placed) {
            try{
                int xCoord, yCoord;
                bool isVertical;
                std::cout << "Enter coordinates (X Y) and orientation (0 - horizontal, 1 - vertical) for a ship of length:" << ship->getSegments().size() << ": " << std::endl;
                std::cin >> xCoord >> yCoord >> isVertical;
                Coordinates coords = {xCoord, yCoord};
                
                if (isVertical == 0){
                    field.placeShip(ship, coords, Orientation::Horizontal);
                    placed = true;
                }else if (isVertical == 1){
                    field.placeShip(ship, coords, Orientation::Vertical);
                    placed = true;
                }
                
            }catch (PlaceShipError &e) {
                std::cout << e.what() << "Try again.\n" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    
    drawer.draw(field, true);

    std::cout << "Enter coordinates to attack (x y), or 'ability' to use a special ability, or 'end' to finish the game\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        std::cout << "Your turn: \n";
        std::string input;
        std::getline(std::cin, input);

        if (input == "end") {
            std::cout << "The game is over";
            break;
        } else if (input == "ability") {
            try{
                abilityManager.methodAbility();
                
            }catch(AbilityError &e){
                std::cout << e.what() << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            }
            
        } else {
            int x, y;
            std::istringstream ss(input);
            if (ss >> x >> y) {
                try{
                    Coordinates coord = {x, y};
                    bool result = field.attackCell(coord);
                    if (result == true){
                    std::cout << "You have received a new ability!\n";
                    abilityManager.addRandomAbility();
                }
                }catch(AttackError &e){
                    std::cout << e.what() << std::endl;
                }
                

                if (manager.allShipsDestroyed()) {
                    std::cout << "Congratulations! All the ships are destroyed, you have won";
                    break;
                }
            } else {
                std::cout << "Incorrect input. Enter the coordinates 'x y', 'ability' or 'end'\n";
            }
        }
    }

    drawer.draw(field, false);
    drawer.draw(field, true);
    manager.printShipsInfo();

    return 0;
}