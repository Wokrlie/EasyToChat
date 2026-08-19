#include "Conver.h"
#include "Message.h"
#include "Time.h"
#include "auth/UUID.h"

Conver::Conver() {
    messages_.push_back({
        UUIDGenerator::instance().generate(),
        SenderType::System,
        "system",
        "There isn't any messages, try to send some.",
        get_current_time()
    });
}

void Conver::receive_message(Message message) {
    if (messages_.size() == 0 && messages_[0].sender_type == SenderType::System) {
        messages_.clear();
    }
    messages_.push_back(message);
}

void Conver::receive_user(User user) {
    auto content = "User " + user.nickname + " enter the conversation. ";
    messages_.push_back({
        UUIDGenerator::instance().generate(),
        SenderType::System,
        "system",
        content,
        get_current_time()
    });
    users_.push_back(user);
}
