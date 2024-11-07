#include "FieldDrawer.hpp"
#include <iomanip>

void FieldDrawer::draw(GameField& field, bool showShips) const {
    int width = field.getWidth();
    int height = field.getHeight();
    const std::vector<FieldCell>& cells = field.getField();

    std::cout << "  ";
    for(int x = 0; x < width; ++x){
        std::cout << " " << x;
    }
    std::cout << std::endl;

    for(int y = 0; y < height; ++y){
        std::cout << std::setw(2) << y;
        for(int x = 0; x < width; ++x){
            int index = y * width + x;
            const FieldCell& cell = cells[index];

            char displayChar = '~';

            if(cell.status == CellStatus::Open){
                if(cell.value == CellValue::Miss){
                    displayChar = 'o';
                }
                else if(cell.value == CellValue::ShipSegment){
                    if(cell.shipSegment->getStatus() == SegmentStatus::Unbroken){
                        displayChar = 'S';
                    }
                    else if(cell.shipSegment->getStatus() == SegmentStatus::Damaged){
                        displayChar = 'D';
                    }
                    else if(cell.shipSegment->getStatus() == SegmentStatus::Destroyed){
                        displayChar = 'X';
                    }
                }
            }
            else {
                if(showShips && cell.value == CellValue::ShipSegment){
                    displayChar = 'S';
                }
                else {
                    displayChar = '~'; 
                }
            }

            std::cout << " " << displayChar;
        }
        std::cout << std::endl;
    }
}
