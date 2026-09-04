#pragma once
#include <cstddef>
#include <vector>

#include "Message.h"
#include "User.h"
#include <uuid.h>

struct ConverID {
    uuids::uuid id;
    std::string to_string() const { return uuids::to_string(id); }
    operator uuids::uuid() const { return id; }
    bool operator==(const ConverID& other) const {
        return id == other.id;
    }
};

// Hash functions for unordered_map
namespace std {
    template<>
    struct hash<ConverID> {
        size_t operator()(const ConverID& key) const {
            const auto& uuid_bytes = key.id;
            static_assert(sizeof(uuid_bytes) == 16, "uuid must be 16 bytes");
            std::string_view view(reinterpret_cast<const char*>(&uuid_bytes), sizeof(uuid_bytes));
            return std::hash<std::string_view>{}(view);
        }
    };
};

class Conver {
    public:
        void receive_message(Message message);
        void receive_user(User user);
        Conver(const std::string& name, std::vector<User> users);
        ~Conver();

        const std::string get_name() const { return name_; }
        std::vector<Message> get_message() const { return messages_; }

    private:
        std::string name_;
        std::vector<User> users_;
        std::vector<Message> messages_;
};
