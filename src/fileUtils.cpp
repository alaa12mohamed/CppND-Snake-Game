#include <fstream>
#include "FileUtils.h"
#include <string>
#include <sstream>

ConfigParameters FileUtils::getConfigFromFile()
{
    std::ifstream filestream(FileUtils::configFilePath);
    /// Using 5 as some default value.
    int _numberOfBoosters, _numberOfObstacles = 5;
    if (filestream.is_open())
    {
        std::string line;
        while (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            std::string key, value;
            linestream >> key >> value;
            if (key == FileUtils::numberOfBoostersKey)
            {
                _numberOfBoosters = std::stoi(value);
            }
            else if (key == FileUtils::numberOfObstaclesKey)
            {
                _numberOfObstacles = std::stoi(value);
            }
        }
    }
    return ConfigParameters(_numberOfBoosters, _numberOfObstacles);
}