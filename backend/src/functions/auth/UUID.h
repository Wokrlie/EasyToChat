#pragma once
#include <uuid.h>

class UUIDGenerator {
    public:
        UUIDGenerator();
        ~UUIDGenerator();
        static UUIDGenerator& instance() { static UUIDGenerator instance; return instance; }
        uuids::uuid generate();
    private:
        uuids::uuid_random_generator* gen;
};
