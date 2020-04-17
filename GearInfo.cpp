#include "GearInfo.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>


using namespace gearplot;


void GearInfo::resize(int numTeeth)
{
    teeth.resize(numTeeth);
}

    
void GearInfoImporter::import(const std::string& filename, GearInfo& gear, int toothId, char zone, char side)
{
    std::cout << "Tooth " << toothId << " zone " << zone << " side " << side << " will be imported from file " << filename << "..." << std::endl;
    
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line);
    int partId = 0, geometryId = 0, readToothId = 0;
    char readZone = 0, readSide = 0;
    // Line 1
    sscanf(line.c_str(), "%d %d %c %d %c", &partId, &geometryId, &readZone, &readToothId, &readSide);
    std::cout << "Line 1 read: partId = " << partId << ", geometryId = " << geometryId << ", readZone = " << readZone
        << ", readToothId = " << readToothId << ", readSide = " << readSide << "\n";

    gear.geometryId = geometryId;
    gear.partId = partId;

    std::getline(file, line);
    double num0 = 0.0, num1 = 0.0, num2 = 0.0, num3 = 0.0;
    // Line 2
    sscanf(line.c_str(), "%lf %lf %lf", &num0, &num1, &num2);
    std::cout << "Line 2 numbers: " << num0 << " " << num1 << " " << num2 << std::endl;
    ToothInfo& toothToUpdate = gear.teeth[toothId];
    
    switch (zone)
    {
    case GearInfo::ZONE_PROFILE:
        gear.totalProfileError = num0;
        gear.rootDiameter = num1;
        gear.tipDiameter = num2;
        break;
    case GearInfo::ZONE_LEAD:
        gear.totalLeadError = num0;
        gear.minHeight = num1;
        gear.maxHeight = num2;
        break;
    default:
        break;
    }

    std::getline(file, line);
    // Line 3
    sscanf(line.c_str(), "%lf %lf %lf %lf", &num0, &num1, &num2, &num3);
    std::cout << "Line 3 numbers: " << num0 << " " << num1 << " " << num2 << " " << num3 << std::endl;
    switch (zone)
    {
    case GearInfo::ZONE_PROFILE:
        if (side == GearInfo::SIDE_RIGHT)
        {   
            toothToUpdate.rightProfile.lineAX = num0;
            toothToUpdate.rightProfile.lineAY = num1;
            toothToUpdate.rightProfile.lineBX = num2;
            toothToUpdate.rightProfile.lineBY = num3;
        }
        else if (side == GearInfo::SIDE_LEFT)
        {
            toothToUpdate.leftProfile.lineAX = num0;
            toothToUpdate.leftProfile.lineAY = num1;
            toothToUpdate.leftProfile.lineBX = num2;
            toothToUpdate.leftProfile.lineBY = num3;
        }
        break;
    case GearInfo::ZONE_LEAD:
        if (side == GearInfo::SIDE_RIGHT)
        {
            toothToUpdate.rightLead.lineAX = num0;
            toothToUpdate.rightLead.lineAY = num1;
            toothToUpdate.rightLead.lineBX = num2;
            toothToUpdate.rightLead.lineBY = num3;
        }
        else if (side == GearInfo::SIDE_LEFT)
        {
            toothToUpdate.leftLead.lineAX = num0;
            toothToUpdate.leftLead.lineAY = num1;
            toothToUpdate.leftLead.lineBX = num2;
            toothToUpdate.leftLead.lineBY = num3;
        }
        break;
    
    default:
        break;
    }

    std::getline(file, line);
    // Line 4
    sscanf(line.c_str(), "%lf %lf %lf", &num0, &num1, &num2);
    std::cout << "Line 4 numbers: " << num0 << " " << num1 << " " << num2 << std::endl;
    switch (zone)
    {
    case GearInfo::ZONE_PROFILE:
        if (side == GearInfo::SIDE_RIGHT)
            toothToUpdate.rightProfile.totalProfileError = num0;
        else
            toothToUpdate.leftProfile.totalProfileError = num0;

        gear.totalProfileNegTol = num1;
        gear.totalProfilePosTol = num2;
        
        break;
    case GearInfo::ZONE_LEAD:
        if (side == GearInfo::SIDE_RIGHT)
            toothToUpdate.rightLead.totalLeadError = num0;
        else
            toothToUpdate.leftLead.totalLeadError = num0;
 
        gear.totalLeadNegTol = num1;
        gear.totalLeadPosTol = num2;
        
        break;
    default:
        break;
    }

    std::getline(file, line);
    // Line 5
    sscanf(line.c_str(), "%lf %lf %lf", &num0, &num1, &num2);
    std::cout << "Line 5 numbers: " << num0 << " " << num1 << " " << num2 << std::endl;
    switch (zone)
    {
    case GearInfo::ZONE_PROFILE:
        if (side == GearInfo::SIDE_RIGHT)
            toothToUpdate.rightProfile.formError = num0;
        else if (side == GearInfo::SIDE_LEFT)
            toothToUpdate.leftProfile.formError = num0;

        gear.profileFormNegTol = num1;
        gear.profileFormPosTol = num2;

        break;
    case GearInfo::ZONE_LEAD:
        if (side == GearInfo::SIDE_RIGHT)
            toothToUpdate.rightLead.formError = num0;
        else if (side == GearInfo::SIDE_LEFT)
            toothToUpdate.leftLead.formError = num0;

        gear.leadFormNegTol = num1;
        gear.leadFormPosTol = num2;

        break;
    default:
        break;
    }

    std::getline(file, line);
    // Line 6
    sscanf(line.c_str(), "%lf %lf %lf", &num0, &num1, &num2);
    std::cout << "Line 6 numbers: " << num0 << " " << num1 << " " << num2 << std::endl;
    switch (zone)
    {
    case GearInfo::ZONE_PROFILE:
        if (side == GearInfo::SIDE_RIGHT)
            toothToUpdate.rightProfile.slopeError = num0;
        else if (side == GearInfo::SIDE_LEFT)
            toothToUpdate.leftProfile.slopeError = num0;

        gear.profileSlopeNegTol = num1;
        gear.profileSlopePosTol = num2;
        
        break;
    case GearInfo::ZONE_LEAD:
        if (side == GearInfo::SIDE_RIGHT)
            toothToUpdate.rightLead.helixSlopeError = num0;
        else if (side == GearInfo::SIDE_LEFT)
            toothToUpdate.leftLead.helixSlopeError = num0;

        gear.helixSlopeNegTol = num1;
        gear.helixSlopePosTol = num2;

        break;
    default:
        break;
    }

    std::getline(file, line);
    // Line 7
    sscanf(line.c_str(), "%lf %lf", &num0, &num1);
    std::cout << "Line 7 numbers: " << num0 << " " << num1 << std::endl;
    switch (zone)
    {
    case GearInfo::ZONE_PROFILE:
        if (side == GearInfo::SIDE_RIGHT)
        {
            toothToUpdate.rightProfile.pitchError = num0;
            toothToUpdate.rightProfile.cumulativePitchError = num1;
        }
        else if (side == GearInfo::SIDE_LEFT)
        {
            toothToUpdate.leftProfile.pitchError = num0;
            toothToUpdate.leftProfile.cumulativePitchError = num1;
        }

        break;

    default:
        break;
    }

    std::getline(file, line);
    // Line 8
    sscanf(line.c_str(), "%lf", &num0);
    std::cout << "Line 8 number: " << num0 << std::endl;
    
    if (zone == GearInfo::ZONE_PROFILE)
        toothToUpdate.runoutComponent = num0;

    // Line 9 on: deviations
    while (std::getline(file, line))
    {
        sscanf(line.c_str(), "%lf %lf", &num0, &num1);
        std::cout << "Line 9 numbers: " << num0 << " " << num1 << std::endl;
        switch (zone)
        {
        case GearInfo::ZONE_PROFILE:
            if (side == GearInfo::SIDE_RIGHT)
            {
                //toothToUpdate.rightProfile.deviationX.clear();
                //toothToUpdate.rightProfile.deviationY.clear();
                toothToUpdate.rightProfile.deviationX.push_back(num0);
                toothToUpdate.rightProfile.deviationY.push_back(num1);
            }
            else if (side == GearInfo::SIDE_LEFT)
            {
                //toothToUpdate.leftProfile.deviationX.clear();
                //toothToUpdate.leftProfile.deviationY.clear();
                toothToUpdate.leftProfile.deviationX.push_back(num0);
                toothToUpdate.leftProfile.deviationY.push_back(num1);
            }
            break;
        case GearInfo::ZONE_LEAD:
            if (side == GearInfo::SIDE_RIGHT)
            {
                //toothToUpdate.rightLead.deviationX.clear();
                //toothToUpdate.rightLead.deviationY.clear();
                toothToUpdate.rightLead.deviationX.push_back(num0);
                toothToUpdate.rightLead.deviationY.push_back(num1);
            }
            else if (side == GearInfo::SIDE_LEFT)
            {
                //toothToUpdate.leftLead.deviationX.clear();
                //toothToUpdate.leftLead.deviationY.clear();
                toothToUpdate.leftLead.deviationX.push_back(num0);
                toothToUpdate.leftLead.deviationY.push_back(num1);
            }           
            break;
        default:
            break;
        }
    }

    std::cout << "Toot " << toothId << " right profile: " << toothToUpdate.rightProfile.deviationX.size()
        << ", " << toothToUpdate.rightProfile.deviationY.size() << ", "
        << " left profile: " << toothToUpdate.leftProfile.deviationX.size()
        << ", " << toothToUpdate.leftProfile.deviationY.size() << ", "
        << " right lead: " << toothToUpdate.rightLead.deviationX.size()
        << ", " << toothToUpdate.rightLead.deviationY.size() << ", "
        << " left lead: " << toothToUpdate.leftLead.deviationX.size()
        << ", " << toothToUpdate.leftLead.deviationY.size() << std::endl;

    file.close();
    
    //TODO: implement
}    
