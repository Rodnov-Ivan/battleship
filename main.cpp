#include "GameField.hpp"
#include "ShipManager.hpp"
#include "FieldDrawer.hpp"
#include "Ship.hpp"
#include <vector>
#include "Structures.hpp"

int main(){
    GameField field(-1, -1);

    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    ShipManager manager(shipSizes);

    std::vector<Ship*> ships = manager.getAllShips();

    field.placeShip(ships[0], Coordinates{5, 5}, Orientation::Horizontal);
    field.placeShip(ships[1], Coordinates{6, 1}, Orientation::Horizontal);
    field.placeShip(ships[2], Coordinates{100, 5}, Orientation::Horizontal);//5 3
    field.placeShip(ships[4], Coordinates{2, 8}, Orientation::Vertical);
    field.placeShip(ships[5], Coordinates{6, 5}, Orientation::Horizontal);//5 7
    field.placeShip(ships[3], Coordinates{2, 2}, Orientation::Vertical);
    field.placeShip(ships[6], Coordinates{9, 9}, Orientation::Horizontal);
    field.placeShip(ships[7], Coordinates{0, 4}, Orientation::Horizontal);
    field.placeShip(ships[8], Coordinates{6, 9}, Orientation::Horizontal);
    field.placeShip(ships[9], Coordinates{0, 9}, Orientation::Horizontal);
    

    FieldDrawer drawer;
    std::cout << "Game field(with ships):" << std::endl;
    drawer.draw(field, true);

    std::cout << "\nAttack cell (2, 3):" << std::endl;
    field.attackCell(Coordinates{2, 3});

    std::cout << "\nAttack cell (2, 3):" << std::endl;
    field.attackCell(Coordinates{2, 3});

    std::cout << "\nAttack cell (5, 5):" << std::endl;
    field.attackCell(Coordinates{5, 5});

    std::cout << "\nAttack cell (5, 5):" << std::endl;
    field.attackCell(Coordinates{5, 5});

    std::cout << "\nAttack cell (5, 5):" << std::endl;
    field.attackCell(Coordinates{5, 5});

    std::cout << "\nAttack cell (9, 9):" << std::endl;
    field.attackCell(Coordinates{9, 9});

    std::cout << "\nAttack cell (100, 100):" << std::endl;
    field.attackCell(Coordinates{100, 100});

    std::cout << "\nAttack cell (3, 7):" << std::endl;
    field.attackCell(Coordinates{3, 7});

    std::cout << "\nAttack cell (2, 7):" << std::endl;
    field.attackCell(Coordinates{2, 7});

    std::cout << "\nAttack cell (2, 7):" << std::endl;
    field.attackCell(Coordinates{2, 7});

    std::cout << "\nGame field after attacks(ships are hidden):" << std::endl;
    drawer.draw(field, false);

    manager.printShipsInfo();

    return 0;
}