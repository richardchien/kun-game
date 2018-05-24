#include "./random.h"

#include <random>

using namespace std;

namespace kun::utils {
    unsigned random_int(const unsigned min, const unsigned max) {
        default_random_engine engine;
        engine.seed(random_device()());
        const uniform_int_distribution<unsigned> dist(min, max);
        return dist(engine);
    }
} // namespace kun::utils
