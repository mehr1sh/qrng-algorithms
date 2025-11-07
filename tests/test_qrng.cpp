#include <gtest/gtest.h>
#include "../include/qrng.h"

class QRNGTest : public ::testing::Test {
protected:
    QRNG qrng;
};

TEST_F(QRNGTest, BasicEntropyTest) {
    auto result = qrng.generate(1, 1000);
    EXPECT_GT(result.shannon_entropy, 0.9) << "Shannon entropy should be > 0.9";
}

TEST_F(QRNGTest, FrequencyTest) {
    auto result = qrng.generate(1, 10000);
    // Expect approximately equal number of 0s and 1s
    float ratio = (float)result.ones / (result.ones + result.zeros);
    EXPECT_NEAR(ratio, 0.5, 0.05) << "Bit ratio should be close to 0.5";
}
