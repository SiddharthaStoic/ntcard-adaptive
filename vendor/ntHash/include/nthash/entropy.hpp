/**
 * @file entropy.hpp
 * @brief Rolling entropy calculator for DNA sequences.
 *
 * Efficiently computes Shannon entropy over a sliding window of bases (A, C, G, T).
 * Used to detect complexity variation in real-time during k-mer processing.
 */

#pragma once
#include <array>
#include <string>

namespace nthash {

class RollingEntropy {
public:
    RollingEntropy(int window_size);

    void init(const std::string& window);
    void roll(char out_char, char in_char);
    double compute() const;

private:
    int k_;
    std::array<int, 4> counts;
    std::array<double, 1001> log2_lookup;
    int total;

    void init_lookup();
    inline int base_index(char c) const;
};

} // namespace nthash