#include "GearInfo.h"

#include <iostream>

using namespace gearplot;


void GearInfo::resize(int numTeeth)
{
    teeth.resize(numTeeth);
}

    
void GearInfoImporter::import(const std::string& filename, GearInfo& gear, int toothId, char zone, char side)
{
    std::cout << "Tooth " << toothId << " zone " << zone << " side " << side << " will be imported from file " << filename << "..." << std::endl;
    //TODO: implement
}    
