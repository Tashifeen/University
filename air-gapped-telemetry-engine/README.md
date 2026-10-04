# Air-Gapped Telemetry Engine

A zero-allocation C++17 telemetry and anomaly detection engine designed for safety-critical, offline embedded systems.

## Key Features
* **Zero-Allocation:** Uses a fixed-capacity ring buffer (`std::array`) on the hot loop to prevent heap fragmentation.
* **Polymorphic Evaluator:** Abstract C++ base class supporting interchangeable local rule evaluators.
* **On-Device CART Decision Tree:** Evaluates multi-factor sensor anomalies (thermal, vibration, radiation) locally in SRAM.
* **Simulated Hardware Bus:** Generates continuous register streams with synthetic fault injection.

## Quick Start
```bash
g++ -std=c++17 -O2 main.cpp -o telemetry_engine
./telemetry_engine
