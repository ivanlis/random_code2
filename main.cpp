#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
//#include <boost/xpressive/xpressive.hpp>
#include <set>
#include <regex>

#include "GearInfo.h"

using namespace gearplot;

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << "  part_id geometry_id [directory=./exchange_files]" << std::endl;
        return 1;
    }
    
    SearchInputParameters params;
    params.partId = std::atoi(argv[1]);
    params.geometryId = std::atoi(argv[2]);
    if (argc >= 4)
        params.directory = argv[3];
    else
        params.directory = "./exchange_files";
    if (argc >= 5)
        params.numTeeth = std::atoi(argv[4]);
    else
        params.numTeeth = -1;
    
    
    std::cout << "About to transform the exchange data for part " << params.partId << ", geometry " << params.geometryId
        << ", search directory " << params.directory << ", num. teeth  " << params.numTeeth << "..." << std::endl;

    //std::cout << "Hello." << std::endl;


    boost::filesystem::path searchDirectory(params.directory);

    if (!boost::filesystem::exists(searchDirectory) || !boost::filesystem::is_directory(searchDirectory))
    {
        std::cerr << "Directory " << searchDirectory.string() << " does not exist or is not a directory." << std::endl;
        return 2;
    }

    boost::filesystem::directory_iterator endIt;

    std::string filePatternString = "^" + std::to_string(params.partId) + "_" + std::to_string(params.geometryId) + "_([PL])_([0-9]+)_([LR])\\.txt$";
    std::cout << "filePatternString = " << filePatternString << std::endl;
    std::regex filePattern(filePatternString);

    std::set<int> foundTeeth;

    for (boost::filesystem::directory_iterator dirIt(searchDirectory); dirIt != endIt; ++dirIt)
    {
        std::smatch matchResults;
        boost::filesystem::path item(*dirIt);
        std::string filename = item.filename().string();
        bool result = std::regex_match(filename, matchResults, filePattern, std::regex_constants::match_default);
        if (!result)
            continue;
        //std::cout << "Found entry: " << filename << " matches " << matchResults.size() << std::endl;
        //std::cout << "Match 0: " << matchResults[0] << "\nMatch 1: " << matchResults[1] << "\nMatch 2: " << matchResults[2] << "\nMatch 3: " << matchResults[3] << std::endl;
        //std::cout << "Match 1: " << int(matchResults[1].str()[0]) << std::endl;
        char zoneStr = matchResults[1].str()[0];
        int toothId = std::atoi(matchResults[2].str().c_str());
        char side = matchResults[3].str()[0];
        std::cout << "Found file for zone " << zoneStr << ", tooth id " << toothId << ", side " << side << "." << std::endl;

        foundTeeth.insert(toothId);
    }

    int minToothId = *std::min_element(foundTeeth.begin(), foundTeeth.end());
    int maxToothId = *std::max_element(foundTeeth.begin(), foundTeeth.end());

    std::cout << "Min. tooth id: " << minToothId << ", max. tooth id.: " << maxToothId << std::endl;

    if (params.numTeeth < 0)
        params.numTeeth = maxToothId + 1;

    std::cout << "Number of teeth to use: " << params.numTeeth << "." << std::endl;  

    GearInfo gear;
    gear.resize(params.numTeeth);

    
    for (boost::filesystem::directory_iterator dirIt(searchDirectory); dirIt != endIt; ++dirIt)
    {
        std::smatch matchResults;
        boost::filesystem::path item(*dirIt);
        std::string filename = item.filename().string();
        bool result = std::regex_match(filename, matchResults, filePattern, std::regex_constants::match_default);
        if (!result)
            continue;
        char zoneStr = matchResults[1].str()[0];
        int toothId = std::atoi(matchResults[2].str().c_str());
        char side = matchResults[3].str()[0];            
        
        GearInfoImporter::import(item.string(), gear, toothId, zoneStr, side);
    }

    return 0;
}