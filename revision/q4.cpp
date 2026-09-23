#include <string>
#include <algorithm>

class Book {
    protected:
        double price;
        std::string title;
        int copies;
    public:
        double GetPrice(void) {
            return price;
        }
        void setPrice(double p) {
            price = p;
        }
        std::string GetTitle(void) {
            return title;
        }
        void SetTitle(std::string t) {
            title = t;
        }
        int GetCopies(void) {
            return copies;
        }
        void SetCopies(int c) {
            copies = c;
        }
        bool virtual isLendable(void) { return false; }; // virtual???
};

class PrintedBook : public Book {
    private:
        int *shelf_count;
    public:
        PrintedBook(double price, std::string title,
              int copies, int *shelf_count);
        int* GetShelfCount() {
            return shelf_count;
        }
        void SetShelfCount(int* s) {
            shelf_count = s;
        }
        bool isLendable(void) override {
            return true;
        }
};

class EBook : public Book {
    private:
        int *licence_count;
    public:
        EBook(double price, std::string title, 
            int copies, int *licence_count);
        int* GetLicenceCount(void) {
            return licence_count;
        }
        void SetLicenceCount(int* l) {
            licence_count = l;
        }
        bool isLendable(void) override {
            if (*licence_count > 0) {
                return true;
            } 
            return false;
        }
};

bool LendBook(Book *b) {
    if (b->GetPrice() > 0 && b->GetPrice() <= 500 && b->GetCopies() > 0 && b->isLendable()) {
        b->SetCopies(b->GetCopies() - 1);
        
        PrintedBook* p = dynamic_cast<PrintedBook*>(b);
        EBook*       e = dynamic_cast<EBook*>(b);
        
        if (p && p->GetShelfCount() != nullptr) (*p->GetShelfCount())--;
        if (e && e->GetLicenceCount() != nullptr) (*e->GetLicenceCount())--;
        
        return true;
    }
    return false;
}

Book* FirstLendable(std::vector<Book*> library, double budget) {
    auto it = std::find_if(library.begin(), library.end(), [&budget](Book* b) {
        return b->GetPrice() <= budget && LendBook(b);
    });
    if (it == library.end()) return nullptr;
    return *it;
}
