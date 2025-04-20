#include "Uncompress.h"
#include "nthash/adaptive_hash.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

int k = 15; // default k-mer size
int h = 1;  // number of hashes per spaced seed
double entropy_threshold = 1.5;

void process_file(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << "\n";
        return;
    }

    string line;
    while (getline(infile, line)) {
        // skip headers (for fasta)
        if (!line.empty() && line[0] != '>') {
            adaptive_hash(line, k, h, entropy_threshold);
        }
    }
    infile.close();
}

int main(int argc, char** argv) {
    vector<string> files;

    int opt;
    while ((opt = getopt(argc, argv, "k:h:e:")) != -1) {
        switch (opt) {
            case 'k': k = stoi(optarg); break;
            case 'h': h = stoi(optarg); break;
            case 'e': entropy_threshold = stod(optarg); break;
            default:
                cerr << "Usage: ./ntcard -k <k-mer> -h <hashes per seed> -e <entropy threshold> <files>\n";
                exit(EXIT_FAILURE);
        }
    }

    for (int i = optind; i < argc; ++i)
        files.emplace_back(argv[i]);

#ifdef _OPENMP
    omp_set_num_threads(4);
#endif

#pragma omp parallel for
    for (size_t i = 0; i < files.size(); ++i) {
        process_file(files[i]);
    }

    return 0;
}