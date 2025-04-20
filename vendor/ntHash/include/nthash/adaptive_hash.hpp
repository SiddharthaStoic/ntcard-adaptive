/**
 * @brief Performs adaptive spaced seed hashing on a DNA sequence.
 * 
 * Uses a sliding window entropy calculation to dynamically switch between
 * sparse and dense spaced seed patterns. Optimizes performance in regions
 * with varying complexity.
 * 
 * @param seq Input DNA sequence (ACGT).
 * @param k   k-mer size.
 * @param h   Number of hash functions.
 * @param entropy_threshold Threshold entropy to switch seeds.
 */

#pragma once

#include <string>

void adaptive_hash(const std::string& sequence, int k, int h, double entropy_threshold = 1.5);