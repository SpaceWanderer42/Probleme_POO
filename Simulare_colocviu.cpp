#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


using namespace std;

class Video {

protected:
    string mVideoId;
    uint32_t mLikes{};
    uint32_t mDislikes{};
    uint32_t mViews{};

public:
    Video(const std::string &mVideoId, uint32_t mLikes, uint32_t mDislikes, uint32_t mViews) {
        this->mVideoId = mVideoId;
        this->mLikes = mLikes;
        this->mDislikes = mDislikes;
        this->mViews = mViews;
    }

    void setMVideoId(const string &mVideoId) {
        this->mVideoId = mVideoId;
    }

    void setMLikes(uint32_t mLikes) {
        this->mLikes = mLikes;
    }

    void setMDislikes(uint32_t mDislikes) {
        this->mDislikes = mDislikes;
    }

    void setMViews(uint32_t mViews) {
        this->mViews = mViews;
    }

    Video() = default;


    string getId() const {

        return this->mVideoId;

    }

    uint32_t getDislikes() const {

        return this->mDislikes;
    }

    double getSimpleScore() const {

        return ((double) mLikes / (double) mDislikes) + 1 - (1.0 / (double) mViews);

    }

    virtual double getAdvancedScore() const = 0;

//    virtual double getAdvancedScore() const {
//
//        double r = getSimpleScore();
//
//        if (mVideoId.find("Studiu") != string::npos) {
//            return r * 2;
//        } else if (mVideoId.find("Animale") != string::npos) {
//            return r * 0.75;
//        } else if (mVideoId.find("Sport") != string::npos) {
//            return r * 0.5;
//        }
//        return r;
//    }

    void print(bool simple) const {

        if (simple) {
            double rezultat = getSimpleScore();
            cout << mVideoId << " " << rezultat;
        } else {
            cout << mVideoId;
            getAdvancedScore();

        }
    }

};

class StudyVideo : public Video {

public:

    StudyVideo(const string &mVideoId, uint32_t mLikes, uint32_t mDislikes, uint32_t mViews) : Video(mVideoId, mLikes,
                                                                                                     mDislikes,
                                                                                                     mViews) {}

    double getAdvancedScore() const override {
        return 2 * getSimpleScore();
    }

};

class AnimalVideo : public Video {

public:

    AnimalVideo(const string &mVideoId, uint32_t mLikes, uint32_t mDislikes, uint32_t mViews) : Video(mVideoId, mLikes,
                                                                                                      mDislikes,
                                                                                                      mViews) {}

    double getAdvancedScore() const override {

        return 0.75 * getSimpleScore();

    }

};

class SportsVideo : public Video {

public:

    SportsVideo(const string &mVideoId, uint32_t mLikes, uint32_t mDislikes, uint32_t mViews) : Video(mVideoId, mLikes,
                                                                                                      mDislikes,
                                                                                                      mViews) {}

    double getAdvancedScore() const override {

        return 0.5 * getSimpleScore();

    }

};

class VideoFactory : public Video {

private:
    VideoFactory() = default;

public:

    double getAdvancedScore() const override { return 1; }

    static Video *
    createVideo(const std::string &id, const std::string &type, uint32_t likes, uint32_t dislikes, uint32_t views) {

        Video *video;

        if (type == "Studiu")
            video = new StudyVideo(id, likes, dislikes, views);
        else if (type == "Animale")
            video = new AnimalVideo(id, likes, dislikes, views);
        else if (type == "Sport")
            video = new SportsVideo(id, likes, dislikes, views);
        else
            throw std::invalid_argument("EROARE");
        return video;
    }
};

static bool compareSimple(const Video *a, const Video *b) {
    if (a->getSimpleScore() > b->getSimpleScore())
        return false;
    else {
        if (a->getSimpleScore() < b->getSimpleScore())
            return true;
        else {
            if (a->getSimpleScore() == b->getSimpleScore()) {
                if (a->getDislikes() > b->getDislikes())
                    return false;
                return true;
            }
        }
    }
    return true;
}

static bool compareAdvanced(const Video *a, const Video *b) {
    if (a->getAdvancedScore() > b->getAdvancedScore())
        return false;
    else {
        if (a->getAdvancedScore() < b->getAdvancedScore())
            return true;
        else {
            if (a->getAdvancedScore() == b->getAdvancedScore()) {
                if (a->getDislikes() > b->getDislikes())
                    return false;
                return true;
            }
        }
    }
    return true;
}

int main() {

    uint32_t numberVideos;
    std::cin >> numberVideos;
    vector<Video *> videos;

    for (uint32_t i = 0; i < numberVideos; i++) {

        std::string mVideoId, type;
        uint32_t mLikes, mDislikes, mViews;
        cin >> mVideoId >> type >> mViews >> mLikes >> mDislikes;

        if (type == "Studiu") {
            videos.push_back(new StudyVideo(mVideoId, mLikes, mDislikes, mViews));
        } else if (type == "Animale") {
            videos.push_back(new AnimalVideo(mVideoId, mLikes, mDislikes, mViews));
        } else if (type == "Sport") {
            videos.push_back(new SportsVideo(mVideoId, mLikes, mDislikes, mViews));
        } else {
            cout << "EROARE";
            return 1;
        }
    }

    string cerinta;
    cin >> cerinta;

    if (cerinta == "a") {
        sort(videos.begin(), videos.end(), compareSimple);
        for (auto &video: videos)
            cout << video->getId() << " " << fixed << setprecision(2) << video->getSimpleScore() << "\n";

    } else if (cerinta == "b") {
        double sum = 0;
        for (auto &video: videos)
            sum += video->getSimpleScore();

        for (auto &video: videos)
            if (video->getSimpleScore() > sum / (double) videos.size())
                cout << video->getId() << " " << fixed << setprecision(2) << video->getSimpleScore() << "\n";

    } else if (cerinta == "c") {

        std::string mVideoId, type;
        uint32_t mLikes, mDislikes, mViews;

        while (cin >> mVideoId >> type >> mViews >> mLikes >> mDislikes) {
            int index = -1;
            for (int i = 0; i < videos.size(); i++) {
                if (videos[i]->getId() == mVideoId)
                    index = i;
            }
            if (index >= 0) {
                videos[index]->setMViews(mViews);
                videos[index]->setMLikes(mLikes);
                videos[index]->setMDislikes(mDislikes);
            } else {
                if (type == "Studiu")
                    videos.push_back(new StudyVideo(mVideoId, mLikes, mDislikes, mViews));
                else if (type == "Animale")
                    videos.push_back(new AnimalVideo(mVideoId, mLikes, mDislikes, mViews));
                else if (type == "Sport")
                    videos.push_back(new SportsVideo(mVideoId, mLikes, mDislikes, mViews));
                else {
                    cout << "EROARE";
                    return 1;
                }
            }
        }

        sort(videos.begin(), videos.end(), compareSimple);
        for (auto &video: videos)
            cout << video->getId() << " " << fixed << setprecision(2) << video->getSimpleScore() << "\n";

    } else if (cerinta == "d") {
        sort(videos.begin(), videos.end(), compareAdvanced);
        for (auto &video: videos)
            cout << video->getId() << " " << fixed << setprecision(2) << video->getAdvancedScore() << "\n";
    }
    return 0;
}
