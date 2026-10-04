#include <iostream>
#include <array>
#include <memory>
#include <cmath>
#include <chrono>
#include <thread>
#include <iomanip>
#include <string>


/* 1. DATA STRUCTURE
   Stores raw, uncalibrated telemetry readings from facility hardware sensors.
   In an air-gapped environment, these correspond to memory-mapped registers.
*/

struct TelemetryRegister {
    uint32_t timestamp_ms;  // Hardware clock timestamp (ms)
    float temperature_c;    // Primary thermal sensor (°C)
    float vibration_m_s2;   // Structural accelerometer magnitude (m/s²)
    float radiation_uSv_h;  // Radiation monitor (μSv/h)
};


/* 2. FIXED-CAPACITY RING BUFFER
   
   - In air-gapped safety-critical systems, runtime heap allocation (new/malloc)
     is strictly avoided on hot polling loops to prevent stack/heap collisions.
   - Pre-allocates memory inside std::array at compile time.
   - Modulo arithmetic for tail indexing took a quick trial run to get right, 
     so I kept my debug script in TEST 1 at the bottom to prove the overwrite math works.
*/

template <typename T, size_t Capacity>
class FixedRingBuffer {
private:
    std::array<T, Capacity> buffer_{};
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t size_ = 0;

public:
    constexpr FixedRingBuffer() = default;

    // Push new register sample; overwrites oldest entry if full
    bool push(const T& item) noexcept {
        buffer_[head_] = item;
        head_ = (head_ + 1) % Capacity;
        if (size_ < Capacity) {
            ++size_;
        } else {
            tail_ = (tail_ + 1) % Capacity; // Evict oldest frame
        }
        return true;
    }

    [[nodiscard]] size_t size() const noexcept { return size_; }
    constexpr size_t capacity() const noexcept { return Capacity; }

    // Indexing operator relative to tail (0 = oldest sample currently in SRAM)
    const T& operator[](size_t index) const {
        return buffer_[(tail_ + index) % Capacity];
    }
};


/* 3. EVALUATOR CLASSES & POLYMORPHISM
   
   - Uses an abstract base class (AnomalyEvaluator) so we can swap evaluation rules behind a pointer.
   - Virtual destructor in the base class is mandatory here to prevent undefined behaviour 
     or memory leaks when deleting derived evaluators through a base pointer.
*/

enum class AlertSeverity { NOMINAL, WARNING, CRITICAL_INTERRUPT };

struct EvaluationResult {
    AlertSeverity severity;
    std::string reason;
};

class AnomalyEvaluator {
public:
    virtual ~AnomalyEvaluator() {} // virtual destructor needed for polymorphic deletion
    virtual EvaluationResult evaluate(const TelemetryRegister& sample) const = 0; // pure virtual
};


/* DecisionTreeEvaluator
   Implements an on-device decision tree evaluator based on CART split rules.
   Evaluates thermal runaway at the root, then branches into structural vibration and radiation thresholds.
*/
class DecisionTreeEvaluator : public AnomalyEvaluator {
private:
    float max_temp_c_;
    float max_vib_m_s2_;
    float max_rad_uSv_h_;

public:
    DecisionTreeEvaluator(float max_temp = 75.0f, float max_vib = 0.50f, float max_rad = 2.50f)
        : max_temp_c_(max_temp), max_vib_m_s2_(max_vib), max_rad_uSv_h_(max_rad) {}

    EvaluationResult evaluate(const TelemetryRegister& sample) const override {
        // Root Split: Primary Thermal Runaway Check
        if (sample.temperature_c > max_temp_c_) {
            return {AlertSeverity::CRITICAL_INTERRUPT, 
                    "Thermal Runaway Threshold Exceeded (" + std::to_string(sample.temperature_c) + " °C)"};
        }

        // Secondary Split: Structural Vibration & Radiation Multi-Factor Branch
        if (sample.vibration_m_s2 > max_vib_m_s2_) {
            if (sample.radiation_uSv_h > max_rad_uSv_h_) {
                return {AlertSeverity::CRITICAL_INTERRUPT, 
                        "Compound Structural Shock & Radiation Anomaly Detected"};
            }
            return {AlertSeverity::WARNING, 
                    "Elevated Vibration (" + std::to_string(sample.vibration_m_s2) + " m/s²)"};
        }

        // Isolated Radiation Spike
        if (sample.radiation_uSv_h > max_rad_uSv_h_) {
            return {AlertSeverity::WARNING, 
                    "Elevated Radiation Leakage (" + std::to_string(sample.radiation_uSv_h) + " μSv/h)"};
        }

        return {AlertSeverity::NOMINAL, "Registers operating within nominal safety bounds."};
    }
};


/* 4. HARDWARE BUS SIMULATION
   Simulates continuous register reads from physical sensor hardware over clock cycles.
*/

class HardwareBusSimulator {
private:
    uint32_t clock_ms_ = 0;

public:
    TelemetryRegister read_registers(size_t tick) {
        clock_ms_ += 100;

        // Base nominal telemetry with continuous natural oscillation
        float temp = 42.0f + static_cast<float>(std::sin(tick * 0.1)) * 1.5f;
        float vib  = 0.12f + static_cast<float>(std::cos(tick * 0.2)) * 0.03f;
        float rad  = 0.15f + static_cast<float>(std::sin(tick * 0.05)) * 0.02f;

        // Synthetic fault injections at specific ticks to test local interrupt triggers
        if (tick == 8) {
            vib = 0.68f;  // Structural shock event
        } else if (tick == 15) {
            temp = 84.2f; // Thermal runaway spike
        } else if (tick == 22) {
            vib = 0.72f;
            rad = 3.10f;  // Critical compound fault
        }

        return {clock_ms_, temp, vib, rad};
    }
};


/* 5. MAIN EXECUTION HARNESS
   Runs the real-time telemetry processing loop, evaluating sensor frames in SRAM.
*/

int main() {
    std::cout << "====================================================================\n";
    std::cout << " AIR-GAPPED EMBEDDED TELEMETRY & ANOMALY ENGINE (C++17)\n";
    std::cout << " Architecture: Fixed-SRAM RingBuffer + Polymorphic C++ Decision Tree\n";
    std::cout << " Security Boundary: 100% Offline / Zero Network & Cloud Dependency\n";
    std::cout << "====================================================================\n\n";

    // Fixed capacity ring buffer allocated on stack (32 frames)
    FixedRingBuffer<TelemetryRegister, 32> telemetry_fifo;

    // Polymorphic evaluator stored behind base pointer
    std::unique_ptr<AnomalyEvaluator> evaluator = std::make_unique<DecisionTreeEvaluator>();

    HardwareBusSimulator hardware_bus;

    std::cout << std::left 
              << std::setw(10) << "TIME(ms)"
              << std::setw(12) << "TEMP(°C)"
              << std::setw(14) << "VIB(m/s²)"
              << std::setw(14) << "RAD(μSv/h)"
              << "STATUS / LOCAL HARDWARE INTERRUPT\n";
    std::cout << std::string(75, '-') << "\n";

    for (size_t tick = 1; tick <= 25; ++tick) {
        TelemetryRegister sample = hardware_bus.read_registers(tick);
        telemetry_fifo.push(sample); // Zero dynamic allocation push

        EvaluationResult result = evaluator->evaluate(sample);

        std::cout << std::left 
                  << std::setw(10) << sample.timestamp_ms
                  << std::setw(12) << std::fixed << std::setprecision(1) << sample.temperature_c
                  << std::setw(14) << std::setprecision(3) << sample.vibration_m_s2
                  << std::setw(14) << std::setprecision(2) << sample.radiation_uSv_h;

        if (result.severity == AlertSeverity::NOMINAL) {
            std::cout << "[NOMINAL]\n";
        } else if (result.severity == AlertSeverity::WARNING) {
            std::cout << "[WARNING] " << result.reason << "\n";
        } else if (result.severity == AlertSeverity::CRITICAL_INTERRUPT) {
            std::cout << "!!! [LOCAL INTERRUPT TRIPPED] " << result.reason << " !!!\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }

    std::cout << "\n====================================================================\n";
    std::cout << " MONITORING COMPLETE. Total Telemetry Frames in SRAM: " << telemetry_fifo.size() << "\n";
    std::cout << "====================================================================\n";

    return 0;
}


/* ============================================================================
   OLD TEST MAINS - kept here to show the incremental testing process
   Each block was used to verify one stage before wiring up the full harness.
   Compile command: g++ -std=c++17 -O2 -o engine main.cpp
   ============================================================================ */


// TEST 1: Ring Buffer Indexing & Overwrite Logic
// Checked that pushing past Capacity overwrites the tail cleanly without dynamic heap allocation.
/*
int main() {
    FixedRingBuffer<TelemetryRegister, 3> buffer;
    buffer.push({100, 20.0f, 0.1f, 0.1f});
    buffer.push({200, 21.0f, 0.1f, 0.1f});
    buffer.push({300, 22.0f, 0.1f, 0.1f});
    buffer.push({400, 23.0f, 0.1f, 0.1f}); // Should overwrite entry 100

    std::cout << "Buffer Size: " << buffer.size() << "\n";
    std::cout << "Oldest Timestamp in SRAM: " << buffer[0].timestamp_ms << "\n"; // Expect 200
    return 0;
}
*/
// Output was:
//   Buffer Size: 3
//   Oldest Timestamp in SRAM: 200
// Confirmed modulo math handles wrap-around overwrites cleanly.


// TEST 2: Anomaly Evaluator Split Branches
// Tested that DecisionTreeEvaluator correctly flags thermal runaway vs vibration vs compound faults.
/*
int main() {
    DecisionTreeEvaluator evaluator(75.0f, 0.50f, 2.50f);
    
    TelemetryRegister nominal{100, 40.0f, 0.10f, 0.10f};
    TelemetryRegister thermal{200, 80.0f, 0.10f, 0.10f};
    TelemetryRegister compound{300, 50.0f, 0.60f, 3.00f};

    std::cout << "Nominal severity: " << (int)evaluator.evaluate(nominal).severity << "\n";
    std::cout << "Thermal severity: " << (int)evaluator.evaluate(thermal).severity << "\n";
    std::cout << "Compound severity: " << (int)evaluator.evaluate(compound).severity << "\n";
    return 0;
}
*/
// Output was:
//   Nominal severity: 0 (NOMINAL)
//   Thermal severity: 2 (CRITICAL_INTERRUPT)
//   Compound severity: 2 (CRITICAL_INTERRUPT)
// Confirmed tree splits map to correct severity enum values.
