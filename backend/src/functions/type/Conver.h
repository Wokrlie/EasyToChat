#pragma once
#include <vector>

#include "Message.h"
#include "User.h"
#include <uuid.h>

using ConverID = uuids::uuid;

// Conver is a sync model, add the mutex manully
class Conver {
    public:
        std::vector<Message> get_message() { return messages_; }
        ConverID get_id() { return id_; }
        void receive_message(Message message);
        void receive_user(User user);
        Conver(const std::string& name, std::vector<User> users);
        ~Conver();

    private:
        std::string name_;
        ConverID id_;
        std::vector<User> users_;
        std::vector<Message> messages_;
};
