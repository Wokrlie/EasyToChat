#pragma once
#include <uuid.h>
#include "../type/Conver.h"

class UUIDGenerator {
    public:
        UUIDGenerator();
        ~UUIDGenerator() = default;
        static UUIDGenerator& instance() { static UUIDGenerator instance; return instance; }
        uuids::uuid generate();
    private:
        std::mt19937 engine;
        uuids::uuid_random_generator gen;

        std::mt19937 init_engine();
};

ConverID generate_conver_id();
