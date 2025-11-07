# Detailed Test Results: QRNG vs PRNGs

## Test Environment
- **Date of Testing:** November 7, 2025
- **Machine:** x86_64, Linux
- **Compiler:** g++ 13.3.0
- **Optimization:** -O3

## Test Parameters
- **Sample Sizes:** 1,000 to 100,000 bits
- **Number of Runs:** Multiple per algorithm
- **Statistical Significance Level (α):** 0.05
- **Random Seed:** 42 (for reproducibility)

## Performance Results

### 1. Single Qubit (1,000 shots)
| Metric | Mersenne Twister | Xoshiro256** | PCG | Quantum Simulated |
|--------|-----------------|--------------|-----|-------------------|
| Time (ms) | 0.041 | 0.015 | 0.008 | 0.410 |
| Bits/sec (Mbps) | 24.39 | 66.67 | 125.00 | 2.44 |
| 0s/1s Ratio | 48.6%/51.4% | 49.8%/50.2% | 50.1%/49.9% | 49.9%/50.1% |
| Shannon Entropy | 0.9994 | 0.9999 | 0.9999 | 0.9999 |
| Min Entropy | 0.9602 | 0.9969 | 0.9970 | 0.9969 |

### 2. Multi-Qubit (2 qubits, 10,000 shots)
| Metric | Mersenne Twister |
|--------|-----------------|
| Time (ms) | 0.392 |
| Total Bits | 20,000 |
| 0s/1s Ratio | 49.74%/50.26% |
| Shannon Entropy | 0.99998 |
| Min Entropy | 0.9925 |

### 3. Large Scale Test (100,000 bits)
| Algorithm | Time (ms) | 0s/1s Ratio | Shannon Entropy | Min Entropy | Chi-square p-value | Runs p-value |
|-----------|----------:|------------:|----------------:|------------:|-------------------:|-------------:|
| Mersenne Twister | 2.97 | 50.10/49.90 | 0.999997 | 0.997002 | 0.510696 | 0.774897 |
| Xoshiro256** | 1.06 | 49.90/50.10 | 0.999997 | 0.997117 | 0.527089 | 0.161812 |
| PCG | 0.33 | 50.23/49.77 | 0.999985 | 0.993494 | 0.152904 | 0.785546 |
| Quantum Simulated | 33.21 | 49.89/50.11 | 0.999997 | 0.996916 | 0.498579 | 0.733795 |

## Statistical Analysis

### 1. Randomness Tests
- **All algorithms** passed all statistical tests (p-values > 0.05)
- **Chi-square test**: All p-values between 0.15-0.53 (ideal: ~0.5)
- **Runs test**: All p-values between 0.16-0.79 (ideal: ~0.5)

### 2. Entropy Analysis
- **Shannon Entropy**: All algorithms > 0.999 (max 1.0)
- **Min Entropy**: All algorithms > 0.99 (excellent)

### 3. Performance Analysis
- **PCG** is the fastest (0.33ms for 100k bits)
- **Xoshiro** provides best balance of speed and quality
- **Quantum simulation** is ~100x slower but provides true randomness

## Recommendations

1. **General Use**: PCG (best performance/quality ratio)
2. **Cryptography**: Xoshiro or Mersenne Twister
3. **True Randomness**: Quantum Simulated (when speed is not critical)

[← Back to Overview](../README.md) | [View Testing Methodology](./TESTING_METHODOLOGY.md)