#ifndef FILEUTILS_H
#define FILEUTILS_H

struct ConfigParameters
{
    // Constructor
    ConfigParameters(const int numberOfBoosters,
                     const int numberOfObstacles)
        : _numberOfBoosters(numberOfBoosters),
          _numberOfObstacles(numberOfObstacles){};

    // getters
    int getNumberOfBoosters() const { return _numberOfBoosters; }
    int getNumberOfObstacles() const { return _numberOfObstacles; }

private:
    int _numberOfBoosters;
    int _numberOfObstacles;
};

namespace FileUtils
{
    /// Path
    constexpr char configFilePath[] = "../gameConfig/config.txt";

    /// File Keys

    constexpr char numberOfBoostersKey[] = "numberOfBoosters";
    constexpr char numberOfObstaclesKey[] = "numberOfObstacles";

    /// Config Parameters
    ConfigParameters getConfigFromFile();
}

#endif