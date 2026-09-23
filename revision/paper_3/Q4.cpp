#include <string>
#include <vector>
#include <algorithm>

class Track {
    protected:
        double rating;
        std::string title;
        int duration;
    public:
        double GetRating(void) {
            return rating;
        }
        void SetRating(double r) {
            rating = r;
        }
        std::string GetTitle(void) {
            return title;
        }
        void SetTitle(std::string t) {
            title = t;
        }
        int GetDuration(void) {
            return duration;
        }
        void SetDuration(int d) {
            duration = d;
        }
        virtua bool isPlayable() {
            return false;
        }
};

class MusicTrack : public Track {
    private:
        int *play_count;
    public:    
        MusicTrack(double rating, std::string title, int duration, int *play_count) {
            this->rating = rating;
            this->title = title;
            this->duration = duration;
            this->play_count = play_count;
        }
        
        int* GetPlayCount(void) {
            return play_count;
        }
        void SetPlayCount(int* p) {
            play_count = p;
        }
        bool isPlayable() override {
            return true;
        }
};

class Podcast : public Track {
    private:
        int *episode_number;
    public:    
        Podcast(double rating, std::string title,
          int duration, int *episode_number) {
            this->rating = rating;
            this->title = title;
            this->duration = duration;
            this->episode_number = episode_number;
        }
        
        int* GetEpisodeNumber(void) {
            return episode_number;
        }
        void SetEpisodeNumber(int* e) {
            episode_number = e;
        }
        bool isPlayable() override {
            if (*episode_number > 0) {
                return true;
            }
            return false;
        }
};


bool PlayTrack(Track *t) {
    if (t->GetRating() >= 0 && t->GetRating() <= 5 && t->GetDuration() > 0 && t->isPlayable()) {
        MusicTrack* m = dynamic_cast<MusicTrack*>(t);
        Podcast* p = dynamic_cast<Podcast*>(t);
        if (m && m->GetPlayCount() != nullptr) {
            (*m->GetPlayCount())++;
        }
        if (p && p->GetEpisodeNumber() != nullptr) {
            (*p->GetEpisodeNumber())++;
        }
        return true;
    }
    return false;
}

bool AllPlayable(std::vector<Track*> playlist, double min_rating) {
    bool result = std::all_of(playlist.begin(), playlist.end(),
                    [min_rating](Track* t){ 
                        if (PlayTrack(t) && t->GetRating() >= min_rating) {
                            return true;
                        }
                        return false;
                    });
    return result;
}
