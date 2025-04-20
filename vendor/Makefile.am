# Static library
noinst_LIBRARIES = libnthash.a

# Source files for the static library
libnthash_a_SOURCES = \
    nthash/src/seed.cpp \
    nthash/src/kmer.cpp \
    nthash/src/adaptive_hash.cpp \
    nthash/src/entropy.cpp

# Include paths for compiling the static library
libnthash_a_CPPFLAGS = \
    -I$(srcdir)/nthash/include \
    -I$(srcdir)/nthash

# Public headers to be installed or used by parent project
noinst_HEADERS = \
    nthash/include/nthash/nthash.hpp \
    nthash/include/nthash/adaptive_hash.hpp \
    nthash/include/nthash/entropy.hpp \
    nthash/include/nthash/adaptive_seed.hpp