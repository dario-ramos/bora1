#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "videogame.h"
#include "string_utils.h"
using namespace VideoGames;
using namespace std;

bool FileExists(const std::string& fileName) {
    std::ifstream infile(fileName);
    return infile.good();
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

void ReadPublishersFile(const string& publisherFileName, vector<VideoGame>& videoGames) {
    string line;
    ifstream publishersFile(publisherFileName);
    while (std::getline(publishersFile, line)) {
        int iDelimiter = line.find_first_of(';');
        string publisherName = line.substr(0, iDelimiter);
        publisherName = StringUtils::Trim(publisherName);
        string gameName = line.substr(iDelimiter+1);
        gameName = StringUtils::RemoveExtraSpaces(gameName);
        gameName = StringUtils::Trim(gameName);
        if (!VideoGames::VideoGameExists(videoGames, gameName)) {
            VideoGames::AddVideoGame(videoGames, gameName, publisherName, 0);
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
        cout << rating << endl;
        string gameName;
        string word;
        while (ssLine >> word) {
            gameName += (word + ' ');
        }
        gameName = StringUtils::Trim(gameName);
        if (!VideoGames::VideoGameExists(videoGames, gameName)) {
            VideoGames::AddVideoGame(videoGames, gameName, "", rating);
        }
        else {
            VideoGames::AddVideoGameRating(videoGames, gameName, rating);
        }
    }
}

void main() {
    try {
        string publisherFileName = "publishers.txt";//ReadInputFileName("Publisher");
        string ratingsFileName = "ratings.txt";//ReadInputFileName("Ratings");
        string outputFileName = "outputs.txt";//ReadOutputFileName();
        vector<VideoGame> videoGames;
        ReadPublishersFile(publisherFileName, videoGames);
        ReadRatingsFile(ratingsFileName, videoGames);
        VideoGames::SortByRating(videoGames);
        system("PAUSE");
    }
    catch (exception ex) {
        cerr << "Fatal error: " << ex.what() << endl;
    }
}