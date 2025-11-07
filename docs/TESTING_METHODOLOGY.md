# Testing Methodology

## Tested Algorithms
1. **QRNG** - Simulated quantum measurement
2. **Mersenne Twister (MT19937)** - Industry standard
3. **Xorshift** - Fast, lightweight
4. **PCG** - Modern alternative
5. **LCG** - Simple baseline

## Test Environment
- **CPU**: Intel Core i5-1035G1
- **OS**: Ubuntu 22.04 LTS
- **Compiler**: g++ 11.4.0
- **Build**: CMake 3.22.1

## Testing Methodology

### 1. Speed Testing
**Objective:** Measure how many random bits each algorithm can generate per second.

**Procedure:**
1. For each algorithm, generate 1,000,000 random bits
2. Measure the time taken using `std::chrono::high_resolution_clock`
3. Calculate bits per second: `(1,000,000 bits) / (time in seconds)`
4. Repeat 10 times and take the average

### 2. Statistical Testing

#### a) Frequency Test (Monobit Test)
**Purpose:** Verifies if the number of 0s and 1s are approximately equal.

**Method:**
1. Count the number of 1s in the sequence
2. Calculate the test statistic: S = (count - n/2) / √(n/4)
3. Compute p-value = erfc(|S|/√2)
4. Pass if p-value > 0.01

#### b) Runs Test
**Purpose:** Tests the number of runs (sequences of identical bits) to detect patterns.

**Method:**
1. Count the number of runs (both 0-runs and 1-runs)
2. Calculate expected runs and variance
3. Compute z-score and p-value
4. Pass if p-value > 0.01

#### c) Chi-Square Test
**Purpose:** Tests the distribution of 0s and 1s.

**Method:**
1. Count occurrences of 0s and 1s
2. Calculate χ² = Σ((observed - expected)² / expected)
3. Compute p-value using chi-square distribution with 1 degree of freedom
4. Pass if p-value > 0.01

### 3. Entropy Measurement

#### a) Shannon Entropy
**Formula:** H = -Σ(p(x) * log₂(p(x)))
- Where p(x) is the probability of each outcome (0 or 1)
- Perfect random sequence has entropy = 1.0

#### b) Min-Entropy
**Formula:** H_min = -log₂(max(p, 1-p))
- Where p is the probability of the most common bit
- Measures worst-case predictability

### 4. Security Analysis
**Method:**
- Review of cryptographic literature for known vulnerabilities
- Analysis of state size and period
- Evaluation of prediction resistance

## Testing Parameters
- Sample size: 1,000,000 bits per test run
- Number of runs: 10 per algorithm
- Statistical significance level: α = 0.01
- Random seed: System time (except for reproducibility tests)

## Data Collection
All test results were automatically logged to CSV files with timestamps. The following data was recorded for each test run:
- Algorithm name
- Timestamp
- Execution time (ms)
- Bits generated
- Statistical test results
- Entropy measurements

## Analysis Tools
- Python 3.10 with NumPy, SciPy, and Matplotlib for data analysis
- Jupyter Notebook for interactive exploration
- Gnuplot for generating publication-quality graphs

## Limitations
1. **QRNG Simulation:** The QRNG is simulated on classical hardware, which may not fully capture quantum behavior.
2. **Test Coverage:** Only three statistical tests were used instead of the full NIST SP 800-22 suite.
3. **Sample Size:** 1,000,000 bits per test may not be sufficient to detect all patterns.
4. **Hardware Dependencies:** Results may vary across different hardware architectures.

## Reproducibility
To reproduce these tests:
1. Clone the repository
2. Install dependencies: `sudo apt-get install build-essential cmake`
3. Build the project: `mkdir build && cd build && cmake .. && make`
4. Run tests: `./test_runner --samples 1000000 --runs 10`

## Conclusion
This methodology provides a systematic approach to evaluating random number generators. By testing multiple dimensions of randomness, we can make informed decisions about which algorithm is best suited for different applications.

[Next: Detailed Results →](DETAILED_RESULTS.md)