#include "UUID.h"
#include <algorithm>
#include <iterator>
#include <random>
#include <uuid.h>

UUIDGenerator::UUIDGenerator() {
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 generator(seq);
    gen = new uuids::uuid_random_generator{generator};
}

UUIDGenerator::~UUIDGenerator() {
    delete gen;
}

uuids::uuid UUIDGenerator::generate() {
    auto generator = *gen;
    return generator();
}
