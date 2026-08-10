#pragma once
#include <vector>

#include "Message.h"
#include "User.h"
#include <uuid.h>

using ConverID = std::string;

// Conver is a sync model, add the mutex manully
class Conver {
    public:
        std::vector<Message> get_message() { return messages_; }
        void receive_message(Message message);
        void receive_user(User user);
        Conver();
        ~Conver();

    private:
        std::string name_;
        std::vector<User> users_;
        std::vector<Message> messages_;
};
