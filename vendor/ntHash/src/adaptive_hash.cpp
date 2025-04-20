/**
 * @file adaptive_hash.cpp
 * @brief Adaptive entropy-based spaced seed hashing implementation.
 *
 * Dynamically switches between sparse and dense spaced seeds based on local Shannon entropy.
 * Optimizes hashing in low- and high-complexity genomic regions for performance.
 */

 #include "nthash/nthash.hpp"
 #include "nthash/entropy.hpp"
 
 #include <iostream>
 #include <chrono>
 
 void adaptive_hash(const std::string& seq, int k, int h, double entropy_threshold = 1.5) {
     std::cout << "[AdaptiveHash] Using adaptive spaced seed hashing with entropy threshold = " 
               << entropy_threshold << std::endl;
 
     const size_t len = seq.size();
     if (len < static_cast<size_t>(k)) {
         std::cerr << "[AdaptiveHash] Sequence too short. Skipping.\n";
         return;
     }
 
     // Dynamically create seeds that match the input k
     std::string dense_seed_str(k, '1');
     std::string sparse_seed_str;
     for (int i = 0; i < k; ++i)
         sparse_seed_str += (i % 3 == 0) ? '1' : '0';
 
     std::vector<std::string> DENSE_SEED  = { dense_seed_str };
     std::vector<std::string> SPARSE_SEED = { sparse_seed_str };
 
     const std::string init_kmer = seq.substr(0, k);
     const char* p = seq.data();
 
     nthash::RollingEntropy entropy_calc(k);
     entropy_calc.init(init_kmer);
 
     // Stack-allocated hashers (faster than unique_ptr)
     nthash::SeedNtHash dense_hasher(init_kmer, DENSE_SEED, h, k);
     nthash::SeedNtHash sparse_hasher(init_kmer, SPARSE_SEED, h, k);
 
     dense_hasher.roll();
     sparse_hasher.roll();
 
     bool use_dense = false;
     int dense_count = 0;
     int sparse_count = 0;
 
     auto start = std::chrono::high_resolution_clock::now();
 
     for (int i = k; i < static_cast<int>(len); ++i) {
         entropy_calc.roll(p[i - k], p[i]);
         double entropy = entropy_calc.compute();
 
         use_dense = (entropy > entropy_threshold);
 
         if (use_dense) {
             dense_hasher.roll();
             dense_count++;
         } else {
             sparse_hasher.roll();
             sparse_count++;
         }
     }
 
     auto end = std::chrono::high_resolution_clock::now();
     double elapsed_sec = std::chrono::duration<double>(end - start).count();
 
     int total_hashes = dense_count + sparse_count;
     std::cout << "[AdaptiveHash] Dense seeds used: " << dense_count 
               << ", Sparse seeds used: " << sparse_count << std::endl;
     std::cout << "[AdaptiveHash] Total adaptive hashes generated: " << total_hashes << std::endl;
     std::cout << "[AdaptiveHash] Adaptive hashing completed in " << elapsed_sec << " seconds.\n";
 } 