/// Copyright (c) 2023 Araf Al Jami
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <unistd.h>

int main(int argc, char** argv) {
    cpr::Response r = cpr::Get(cpr::Url{"https://codeforces.com/api/user.rating?handle=" + username});
    if (r.status_code != 200) {
        return -1;
    }

    auto json = nlohmann::json::parse(r.text);
    if (json["status"] != "OK") {
        return -1;
    }

    if (json["result"].empty()) {
        return -1;
    }

    auto latestChange = json["result"].back();
    std::string homeDir = getenv("HOME");
    auto filename = homeDir + "/.cfrc_" + username + ".dat";
    std::ifstream in(filename);
    int previousRatingUpdateTimeSeconds = 0;
    in >> previousRatingUpdateTimeSeconds;
    in.close();
    if (previousRatingUpdateTimeSeconds >= latestChange["ratingUpdateTimeSeconds"]) {
        return 0;
    }

    previousRatingUpdateTimeSeconds = latestChange["ratingUpdateTimeSeconds"];
    std::ofstream out(filename);
    out << previousRatingUpdateTimeSeconds << "\n";
    out.close();
    int newRating = latestChange["newRating"];
    int oldRating = latestChange["oldRating"];
    int ratingChanged = newRating - oldRating;
    std::stringstream buffer;
    buffer << "CodeForces rating changed by " << ratingChanged << " !! OldRating: " << oldRating
        << " NewRating: " << newRating << "\n";
    std::cout << buffer.str() << "\n";

    // std::string discordWebhookUrl = "";
    // cpr::Post(cpr::Url{discordWebhookUrl},
    //           cpr::Payload{{"content", buffer.str()}});
    return 0;
}
