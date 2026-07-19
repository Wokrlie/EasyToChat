import axios from "axios";
import type { Message } from "@/types/message";

const apiClient = axios.create({
  baseURL: "/api",
  timeout: 5000,
});

export const chatApi = {
  getMessages() {
    return apiClient.get<Message[]>("/messages")
  },
  sendMessage(content: string, senderName: string = 'User') {
    return apiClient.post("/messages", {
      content,
      sender_type: "user",
      sender_name: senderName,
    });
  }
};
