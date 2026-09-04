#include "UUID.h"
#include <chrono>
#include <random>
#include <uuid.h>

UUIDGenerator::UUIDGenerator() : engine(init_engine()), gen(engine) {
}

std::mt19937 UUIDGenerator::init_engine() {
    std::random_device rd;
    std::array<unsigned, 8> seeds;
    seeds[0] = rd();
    seeds[1] = static_cast<unsigned>(
        std::chrono::steady_clock::now().time_since_epoch().count()
    );
    std::seed_seq seq(seeds.begin(), seeds.end());
    return std::mt19937(seq);
}

uuids::uuid UUIDGenerator::generate() {
    return gen();
}

ConverID generate_conver_id() {
    return { UUIDGenerator::instance().generate() };
}
