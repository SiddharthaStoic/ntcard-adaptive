#pragma once

#include "nthash.hpp"
#include <string>
#include <vector>
#include <array>

namespace nthash {

class AdaptiveSeedNtHash {
public:
  AdaptiveSeedNtHash(const std::string& seq,
                     const std::vector<std::string>& dense_seeds,
                     const std::vector<std::string>& sparse_seeds,
                     unsigned h, unsigned k, unsigned window_size = 30);

  bool roll();
  const uint64_t* hashes() const;

private:
  double compute_entropy(const std::string& window);
  void select_seed(size_t pos);

  std::string seq;
  std::vector<std::string> dense_seeds;
  std::vector<std::string> sparse_seeds;
  unsigned k, h, window_size;
  size_t pos = 0;

  std::unique_ptr<SeedNtHash> current_hasher;
  std::vector<uint64_t> hash_vals;
};

} // namespace nthash