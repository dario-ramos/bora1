#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../Lib/Sort/sortall.h"
#include "../Lib/Sort/comparer.h"
using namespace std;

struct VideoGame {
    float           Rating;
    int             RatingsCount;
    std::string     Name;
    std::string     Publisher;
};

bool FileExists(const std::string& fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}

string Trim(const string& s) {
    string result = s;
    size_t p = result.find_first_not_of(" \t");
    if (string::npos != p) {
        result.erase(0, p);
    }
    p = result.find_last_not_of(" \t");
    if (string::npos != p) {
        result.erase(p + 1);
    }
    return result;
}

string ToUpper(const string& s) {
    string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

bool VideoGameNameMatches(const VideoGame& game, const string name) {
    return ToUpper(Trim(game.Name)) == ToUpper(Trim(name));
}

bool VideoGameExists(const vector<VideoGame>& videoGames, const string gameName) {
    for (size_t i = 0; i < videoGames.size(); i++) {
        if (VideoGameNameMatches(videoGames[i], gameName)) {
            return true;
        }
    }
    return false;
}

void AddVideoGame(std::vector<VideoGame>& videoGames, const std::string& gameName, const std::string& publisherName, float rating) {
    VideoGame newGame;
    newGame.Name = ToUpper(gameName);
    newGame.Publisher = publisherName;
    newGame.Rating = rating;
    newGame.RatingsCount = 0;
    videoGames.push_back(newGame);
}

void AddVideoGameRating(std::vector<VideoGame>& videoGames, const std::string& gameName, float rating) {
    for (size_t i = 0; i < videoGames.size(); i++) {
        if (VideoGameNameMatches(videoGames[i], gameName)) {
            videoGames[i].RatingsCount = videoGames[i].RatingsCount + 1;
            videoGames[i].Rating = videoGames[i].Rating + (rating - videoGames[i].Rating) / videoGames[i].RatingsCount;
            return;
        }
    }
}

struct DescendingRatingCompare {

    int compare(const VideoGame& game1, const VideoGame& game2) const {
        if (game1.Rating > game2.Rating) {
            return -1;
        }
        else if (game1.Rating < game2.Rating) {
            return 1;
        }
        else {
            return 0;
        }
    }
};

void SortByRating(vector<VideoGame>& videoGames) {
    QuickSort(videoGames, videoGames.size(), DescendingRatingCompare());
}

string ReadInputFileName(const std::string& fileType) {
    bool fileExists = false;
    string fileName;
    while (!fileExists) {
        cout << "Please enter a filename for the " + fileType + " file: " << endl;
        cin >> fileName;
        fileExists = FileExists(fileName);
        if (!fileExists) {
            cout << "Cannot open the " << fileType << " file" << endl;
        }
    }
    return fileName;
}

string ReadOutputFileName() {
    cout << "Please enter a filename for output file" << endl;
    string outputFileName;
    cin >> outputFileName;
    return outputFileName;
}

string RemoveExtraSpaces(const string &sentence) {
    stringstream sstream;
    string str, newoutput;
    sstream << sentence;
    while (sstream >> str) {
        newoutput += (str + ' ');
    }
    return newoutput.substr(0, newoutput.length() - 1);
}

void ReadPublishersFile(const string& publisherFileName, vector<VideoGame>& videoGames) {
    string line;
    ifstream publishersFile(publisherFileName);
    while (std::getline(publishersFile, line)) {
        int iDelimiter = line.find_first_of(';');
        string publisherName = line.substr(0, iDelimiter);
        publisherName = Trim(publisherName);
        string gameName = line.substr(iDelimiter+1);
        gameName = RemoveExtraSpaces(gameName);
        gameName = Trim(gameName);
        if (!VideoGameExists(videoGames, gameName)) {
            AddVideoGame(videoGames, gameName, publisherName, 0);
        }
    }
}

void ReadRatingsFile(const string& ratingsFileName, vector<VideoGame>& videoGames) {
    string line;
    ifstream ratingsFile(ratingsFileName);
    while (std::getline(ratingsFile, line)) {
        float rating;
        stringstream ssLine(line);
        ssLine >> rating;
        string gameName;
        string word;
        while (ssLine >> word) {
            gameName += (word + ' ');
        }
        gameName = Trim(gameName);
        if (!VideoGameExists(videoGames, gameName)) {
            AddVideoGame(videoGames, gameName, "", rating);
        }
        else {
            AddVideoGameRating(videoGames, gameName, rating);
        }
    }
}

void WriteToOutputFile(const string& outputFileName, vector<VideoGame>& videoGames) {
    std::ofstream output(outputFileName, std::ofstream::trunc);
    output << "RANK,NAME,DIRECTOR,POINTS" << endl;
    for (size_t i = 0; i < videoGames.size(); i++) {
        output << i+1 << ", " << videoGames[i].Name << ", " << videoGames[i].Publisher << ", " << videoGames[i].Rating << endl;
    }
    cout << "Results are in the file: " << outputFileName << endl;
}

void main() {
    try {
        string publisherFileName = ReadInputFileName("Publisher");
        string ratingsFileName = ReadInputFileName("Ratings");
        string outputFileName = ReadOutputFileName();
        vector<VideoGame> videoGames;
        ReadPublishersFile(publisherFileName, videoGames);
        ReadRatingsFile(ratingsFileName, videoGames);
        SortByRating(videoGames);
        WriteToOutputFile(outputFileName, videoGames);
        system("PAUSE");
    }
    catch (exception ex) {
        cerr << "Fatal error: " << ex.what() << endl;
    }
}