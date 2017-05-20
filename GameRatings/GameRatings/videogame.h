#pragma once
#include <string>
#include <vector>

namespace VideoGames {

    struct VideoGame {
        float           Rating;
        int             RatingsCount;
        std::string     Name;
        std::string     Publisher;
    };

    bool VideoGameExists(const std::vector<VideoGame>& videoGames, const std::string gameName);

    void AddVideoGame(std::vector<VideoGame>& videoGames, const std::string& gameName, const std::string& publisher, float rating);

    void AddVideoGameRating(std::vector<VideoGame>& videoGames, const std::string& gameName, float rating);

    void SortByRating(std::vector<VideoGame>& videoGames);

}