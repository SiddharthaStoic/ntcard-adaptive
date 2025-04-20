/**
 * @file entropy.cpp
 * @brief Implementation of the RollingEntropy class.
 *
 * Maintains base frequencies and updates entropy efficiently using a rolling window.
 */

#include "nthash/entropy.hpp"
#include "nthash/adaptive_hash.hpp"
#include <cmath>

namespace nthash {

RollingEntropy::RollingEntropy(int window_size)
    : k_(window_size), counts{0, 0, 0, 0}, total(0) {
    init_lookup();
}

void RollingEntropy::init(const std::string& window) {
    counts = {0, 0, 0, 0};
    total = window.size();
    for (char c : window) {
        int idx = base_index(c);
        if (idx >= 0) counts[idx]++;
    }
}

void RollingEntropy::roll(char out_char, char in_char) {
    int out_idx = base_index(out_char);
    int in_idx = base_index(in_char);
    if (out_idx >= 0) counts[out_idx]--;
    if (in_idx >= 0) counts[in_idx]++;
}

double RollingEntropy::compute() const {
    double entropy = 0.0;
    for (int count : counts) {
        if (count == 0) continue;
        int p_scaled = (count * 1000) / total;
        entropy -= log2_lookup[p_scaled];
    }
    return entropy;
}

void RollingEntropy::init_lookup() {
    for (int i = 1; i <= 1000; ++i) {
        double p = static_cast<double>(i) / 1000;
        log2_lookup[i] = p * std::log2(p);
    }
    log2_lookup[0] = 0.0;
}

int RollingEntropy::base_index(char c) const {
    switch (c) {
        case 'A': case 'a': return 0;
        case 'C': case 'c': return 1;
        case 'G': case 'g': return 2;
        case 'T': case 't': return 3;
        default: return 0; // treat unknown as A
    }
}

} // namespace nthash