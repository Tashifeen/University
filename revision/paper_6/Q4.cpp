#include <string>
#include <vector>
#include <algorithm>

class Student {
    protected:
        double grade;
        std::string username;
        int year;
    public:
        double GetGrade(void) {
            return grade;
        }
        void SetGrade(double g) {
            grade = g;
        }
        std::string GetUsername(void) {
            return username;
        }
        void SetUsername(std::string u) {
            username = u;
        }
        int GetYear(void) {
            return year;
        }
        void SetYear(int y) {
            year = y;
        }
        virtual bool isEligible() { return false; }
};

class UndergradStudent : public Student {
    protected:
        int *modules_remaining;
    public:
        UndergradStudent(double grade, std::string username,
                       int year, int *modules_remaining) {
                           this->grade = grade;
                           this->username = username;
                           this->year = year;
                           this->modules_remaining = modules_remaining;
                       }
        int* GetModulesRemaining(void) {
            return modules_remaining;
        }
        void SetModulesRemaining(int* m) {
            modules_remaining = m;
        }
        
        bool isEligible() {
            if (*modules_remaining > 0) {
                return true;
            }
            return false;
        }
};

class PostgradStudent : public Student {
    protected:
        int *research_credits;
    public:
        PostgradStudent(double grade, std::string username,
                  int year, int *research_credits) {
                           this->grade = grade;
                           this->username = username;
                           this->year = year;
                           this->research_credits = research_credits;
                       }
        int* GetResearchCredits(void) {
            return research_credits;
        }
        void SetResearchCredits(int* r) {
            research_credits = r;
        }
        
        bool isEligible() {
            if (*research_credits >= 60) {
                return true;
            }
            return false;
        }
};

bool Enrol(Student *s) {
    if (s->GetGrade() >= 40.0 && s->GetGrade() <= 100 && s->GetYear() > 0 && s->isEligible()) {
        UndergradStudent* u = dynamic_cast<UndergradStudent*>(s);
        PostgradStudent* p = dynamic_cast<PostgradStudent*>(s);
        if (u && u->GetModulesRemaining() != nullptr) {
            (*u->GetModulesRemaining())--;
        }
        if (p && p->GetResearchCredits() != nullptr) {
            (*p->GetResearchCredits())++;
        }
        return true;
    }
    return false;
}

Student* FirstEligible(std::vector<Student*> cohort, int target_year) {
    auto it = std::find_if(cohort.begin(), cohort.end(), [target_year](Student* s){
        if (s->GetYear() == target_year && Enrol(s)) {//return i % 3 == 0;
            return true;
        }
        return false;
    });
    // return nullptr if no such student exists.
    if (it == cohort.end()) return nullptr;
	return *it;
}
