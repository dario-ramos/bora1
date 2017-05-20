#include "videogame.h"
#include "string_utils.h"
#include "../Lib/Sort/sortall.h"
#include "../Lib/Sort/comparer.h"
using namespace std;

bool VideoGameNameMatches(const VideoGames::VideoGame& game, const string name) {
    return StringUtils::ToUpper(StringUtils::Trim(game.Name)) == StringUtils::ToUpper(StringUtils::Trim(name));
}

bool VideoGames::VideoGameExists(const vector<VideoGame>& videoGames, const string gameName) {
    for (size_t i = 0; i < videoGames.size(); i++) {
        if (VideoGameNameMatches(videoGames[i], gameName)) {
            return true;
        }
    }
    return false;
}

void VideoGames::AddVideoGame(std::vector<VideoGame>& videoGames, const std::string& gameName, const std::string& publisherName, float rating) {
    VideoGame newGame;
    newGame.Name = StringUtils::ToUpper(gameName);
    newGame.Publisher = publisherName;
    newGame.Rating = rating;
    newGame.RatingsCount = 0;
    videoGames.push_back(newGame);
}

void VideoGames::AddVideoGameRating(std::vector<VideoGame>& videoGames, const std::string& gameName, float rating) {
    for (size_t i = 0; i < videoGames.size(); i++) {
        if (VideoGameNameMatches(videoGames[i], gameName)) {
            videoGames[i].RatingsCount = videoGames[i].RatingsCount + 1;
            videoGames[i].Rating = videoGames[i].Rating + (rating - videoGames[i].Rating) / videoGames[i].RatingsCount;
            return;
        }
    }
}

struct DescendingRatingCompare {

    int compare(const VideoGames::VideoGame& game1, const VideoGames::VideoGame& game2) const{
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

void VideoGames::SortByRating(vector<VideoGame>& videoGames) {
    QuickSort(videoGames, videoGames.size(), DescendingRatingCompare());
}