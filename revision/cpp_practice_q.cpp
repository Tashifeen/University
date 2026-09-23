class MediaItem {
protected:
    std::string title;
    int year;
    double rating;

public:
    MediaItem(std::string title, int year, double rating)
        : title(title), year(year), rating(rating) {}

    std::string GetTitle() { return title; }
    void SetTitle(std::string t) { title = t; }

    int GetYear() { return year; }
    void SetYear(int y) { year = y; }

    double GetRating() { return rating; }
    void SetRating(double r) { rating = r; }

    virtual bool IsAvailable() { return false; }
};

class Book : public MediaItem {
protected:
    int *pages;

public:
    Book(std::string title, int year, double rating, int *pages)
        : MediaItem(title, year, rating), pages(pages) {}

    int* GetPages() { return pages; }
    void SetPages(int *p) { pages = p; }

    bool IsAvailable() override {
        return pages && *pages > 0;
    }
};

class Movie : public MediaItem {
protected:
    double *duration;

public:
    Movie(std::string title, int year, double rating, double *duration)
        : MediaItem(title, year, rating), duration(duration) {}

    double* GetDuration() { return duration; }
    void SetDuration(double *d) { duration = d; }

    bool IsAvailable() override {
        return duration && *duration >= 30.0;
    }
};

class MediaCollection {
    private:
        MediaItem **items;
        size_t size;
    public:
        // Constructor
        MediaCollection() : items(nullptr), size(0) {}
        
       // Destructor
        ~MediaCollection() {
            for (size_t i = 0; i < size; i++) {
            delete items[i];        // delete each MediaItem
            }
            delete[] items;         // delete the array of pointers
        }
        
        // Copy constructor (deep copy of pointer array, NOT objects)
        MediaCollecton(const MediaCollection &other) {
            size = other.size;
            
            if (size == 0) {
                items = nullptr;
                return;
            }
            
            items = new MediaItem*[size];
            for (size_t i = 0; i < size; i++) {
                items[i] = other.items[i];  // shallow copy of pointers
            }
        }
        // Copy assigment operator
        MediaCollection& operator=(const MediaCollection &other) {
            if (this == &other) return *this;   // self-assignment check
            
            // free old memory
            for (size_t i = 0; i < size; i++) {
                delete items[i];
            }
            delete[] items;
            
            // copy new data
            size = other.size;
            
            if (size == 0) {
                items = nullptr;
                return *this;
            }
            
            items = new MediaItem*[size];
            for (size_t i = 0; i < size; i++) {
                delete items[i];
            }
            return *this;
        }
        
        // Move constructor
        MediaCollection(MediaCollection &&other) noexcept {
            items = other.items;
            size = other.size;
            
            other.items = nullptr;
            other.size = 0;
        }
        
    // Move assignment operator
    MediaCollection& operator=(MediaCollection &&other) noexcept {
        if (this == &other) return *this;

        // free old memory
        for (size_t i = 0; i < size; i++) {
            delete items[i];
        }
        delete[] items;

        // steal resources
        items = other.items;
        size  = other.size;

        // null out source
        other.items = nullptr;
        other.size  = 0;

        return *this;
    }
};













