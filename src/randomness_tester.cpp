#include "randomness_tester.h"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <stdexcept>

RandomnessTester::RandomnessTester(const RandomnessTestConfig& config) 
    : config_(config) {
    // Validate configuration
    if (config_.alpha <= 0.0 || config_.alpha >= 1.0) {
        throw std::invalid_argument("Significance level alpha must be between 0 and 1");
    }
    if (config_.block_size == 0) {
        throw std::invalid_argument("Block size must be at least 1");
    }
    if (config_.template_length < 2) {
        throw std::invalid_argument("Template length must be at least 2");
    }
}

RandomnessTestResult RandomnessTester::test(const std::vector<uint8_t>& bits) const {
    RandomnessTestResult result;
    
    // Run each test and check against significance level
    result.frequency_pvalue = frequency_test(bits);
    result.frequency_test_passed = (result.frequency_pvalue >= config_.alpha);
    
    result.runs_pvalue = runs_test(bits);
    result.runs_test_passed = (result.runs_pvalue >= config_.alpha);
    
    result.chi_square_pvalue = chi_square_test(bits);
    result.chi_square_test_passed = (result.chi_square_pvalue >= config_.alpha);
    
    return result;
}

double RandomnessTester::frequency_test(const std::vector<uint8_t>& bits) const {
    if (bits.empty()) {
        return 0.0;
    }
    
    // Count number of ones
    size_t ones = std::accumulate(bits.begin(), bits.end(), 0);
    size_t n = bits.size();
    
    // Calculate the test statistic (proportion of ones)
    double p_hat = static_cast<double>(ones) / n;
    
    // For a fair coin, p = 0.5
    double p = 0.5;
    
    // Calculate z-score
    double z = (p_hat - p) / std::sqrt(p * (1 - p) / n);
    
    // Two-tailed test: p-value = 2 * (1 - Φ(|z|))
    double p_value = 2.0 * (1.0 - normal_cdf(std::abs(z)));
    
    return p_value;
}

double RandomnessTester::runs_test(const std::vector<uint8_t>& bits) const {
    size_t n = bits.size();
    if (n < 10) {
        return 0.0;  // Not enough data for a meaningful test
    }
    
    // Count number of runs (both 0-runs and 1-runs)
    size_t runs = 1;
    for (size_t i = 1; i < n; ++i) {
        if (bits[i] != bits[i-1]) {
            ++runs;
        }
    }
    
    // Calculate expected value and variance
    double ones = std::accumulate(bits.begin(), bits.end(), 0);
    double p = ones / n;
    double q = 1.0 - p;
    
    double expected_runs = 2.0 * n * p * q + 1.0;
    double variance = (expected_runs - 1.0) * (expected_runs - 2.0) / (n - 1.0);
    
    if (variance == 0.0) {
        return 0.0;  // Not enough variation for a meaningful test
    }
    
    // Calculate z-score
    double z = (runs - expected_runs) / std::sqrt(variance);
    
    // Two-tailed test
    double p_value = 2.0 * (1.0 - normal_cdf(std::abs(z)));
    
    return p_value;
}

double RandomnessTester::chi_square_test(const std::vector<uint8_t>& bits) const {
    // For a binary sequence, we have 2 categories (0 and 1)
    size_t counts[2] = {0, 0};
    
    // Count occurrences of 0 and 1
    for (uint8_t bit : bits) {
        ++counts[bit & 1];
    }
    
    // Expected count for each value (n/2 for a fair coin)
    double expected = bits.size() / 2.0;
    
    // Calculate chi-square statistic
    double chi_square = 0.0;
    for (int i = 0; i < 2; ++i) {
        double diff = counts[i] - expected;
        chi_square += (diff * diff) / expected;
    }
    
    // Degrees of freedom = number of categories - 1 = 1
    // Calculate p-value using chi-square CDF approximation
    double p_value = calculate_p_value(chi_square, 1);
    
    return p_value;
}

double RandomnessTester::calculate_shannon_entropy(const std::vector<uint8_t>& bits) {
    if (bits.empty()) {
        return 0.0;
    }
    
    // Calculate probability of 1s
    double p1 = std::accumulate(bits.begin(), bits.end(), 0.0) / bits.size();
    double p0 = 1.0 - p1;
    
    // Calculate entropy in bits
    double entropy = 0.0;
    if (p0 > 0.0) entropy -= p0 * std::log2(p0);
    if (p1 > 0.0) entropy -= p1 * std::log2(p1);
    
    return entropy;
}

double RandomnessTester::calculate_min_entropy(const std::vector<uint8_t>& bits) {
    if (bits.empty()) {
        return 0.0;
    }
    
    // Calculate probability of the most frequent symbol
    size_t ones = std::accumulate(bits.begin(), bits.end(), 0);
    double max_p = std::max(static_cast<double>(ones) / bits.size(), 
                          1.0 - static_cast<double>(ones) / bits.size());
    
    // Min-entropy is -log2(max_p)
    return -std::log2(max_p);
}

double RandomnessTester::calculate_p_value(double chi_square, size_t degrees_of_freedom) const {
    // For degrees of freedom = 1, we can use the complementary error function
    if (degrees_of_freedom == 1) {
        return erfc(std::sqrt(chi_square / 2.0));
    }
    
    // For other degrees of freedom, we would need to implement the incomplete gamma function
    // This is a simplified approximation
    return std::exp(-chi_square / 2.0);
}

double RandomnessTester::normal_cdf(double x) const {
    // Standard normal CDF using the error function
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

double RandomnessTester::erfc(double x) const {
    // Complementary error function
    return 1.0 - std::erf(x);
}
