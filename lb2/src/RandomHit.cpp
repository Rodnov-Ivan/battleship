#include "RandomHit.hpp"

RandomHit::RandomHit(GameField& field)
	:field(field){};

void RandomHit::useAbility(){
    std::cout << "Bombardment is applying." << std::endl;
    std::vector <std::vector<int>> coordsSegments;
    const std::vector<FieldCell>& fieldplayer = field.getField();
    for(int x = 0; x < field.getWidth(); ++x){
        for (int y = 0; y < field.getHeight(); ++y){
            int index = y * field.getWidth() + x; 
            FieldCell cell = fieldplayer[index];
            if (cell.value == CellValue::ShipSegment 
            && cell.shipSegment->getStatus() != SegmentStatus::Destroyed){
                coordsSegments.push_back({x,y});
            }
        }
    }
    if (!coordsSegments.empty()){
        std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
        const std::vector<FieldCell>& fieldplayer = field.getField();
		std::uniform_int_distribution<> dis(0, coordsSegments.size() - 1);
		int random_number = dis(gen);
        int x = coordsSegments[random_number][0];
        int y = coordsSegments[random_number][1];
        auto& cell = fieldplayer[y*field.getWidth() + x];
        cell.shipSegment->takeDamage();
        
    }
}