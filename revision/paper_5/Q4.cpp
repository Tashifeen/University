#include <string>
#include <algorithm>
#include <vector>

class Patient {
    protected:
        double risk_score;
        std::string name;
        int ward;
    public:
        double GetRiskScore(void) { return risk_score; }
        void SetRiskScore(double r) { risk_score = r; }
        std::string GetName(void) { return name; }
        void SetName(std::string n) { name = n; }
        int GetWard(void) { return ward; }
        void SetWard(int w) { ward = w; }
        
        virtual bool requiresAttention(void) { return false; }
};

class InPatient : public Patient {
    private:
        int *days_admitted;
    public:
        InPatient(double risk_score, std::string name,
            int ward, int *days_admitted) {
                this->risk_score = risk_score;
                this->name = name;
                this->ward = ward;
                this->days_admitted = days_admitted;
            }
        int* GetDaysAdmitted(void) { return days_admitted; }
        void SetDaysAdmitted(int* d) {days_admitted = d; }
        
        bool requiresAttention(void) override {
            if (*days_admitted > 7) {
                return true;
            }
            return false;
        }
};

class OutPatient : public Patient {
    private:
        int *appointments_remaining;
    public:
        OutPatient(double risk_score, std::string name,
             int ward, int *appointments_remaining) {
                this->risk_score = risk_score;
                this->name = name;
                this->ward = ward;
                this->appointments_remaining = appointments_remaining;
            }
        int* GetAppointmentsRemaining(void) { return appointments_remaining; }
        void SetAppointmentsRemaining(int* a) {appointments_remaining = a; }
        
        bool requiresAttention(void) override {
            if (*appointments_remaining > 0) {
                return true;
            }
            return false;
        }
};

bool ReviewPatient(Patient *p) {
    if (p->GetRiskScore() > 0 && p->GetRiskScore() <= 10 && p->GetWard() > 0 && p->requiresAttention()) {
        InPatient* i = dynamic_cast<InPatient*>(p);
        OutPatient* o = dynamic_cast<OutPatient*>(p);
        if (i && i->GetDaysAdmitted() != nullptr) { (*i->GetDaysAdmitted())++; }
        if (o && o->GetAppointmentsRemaining() != nullptr) { (*o->GetAppointmentsRemaining())--; }
        return true;
    }
    return false;
}

int CountAtRisk(std::vector<Patient*> patients,
                  double risk_threshold) {
                      int count = std::count_if(patients.begin(), patients.end(), [risk_threshold](Patient* p){
                          if (p->GetRiskScore() >= risk_threshold && ReviewPatient(p)) {
                              return true;
                          }
                          return false;
                      });
                  return count;
                  }
















