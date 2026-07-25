import axios from 'axios'
import type { Message } from '@/types/message'
import type { User } from '@/types/user'

const apiClient = axios.create({
  baseURL: '/api',
  timeout: 5000,
})

export const chatApi = {
  getMessages() {
    return apiClient.get<Message[]>('/messages')
  },
  sendMessage(content: string, senderName: string = 'User') {
    return apiClient.post('/messages', {
      content,
      sender_type: 'user',
      sender_name: senderName,
    })
  },
  auth_login(username: string) {
    return apiClient.get<User>('/auth/login', {
      params: {
        username,
      },
    })
  },
  auth_register(username: string, nickname: string) {
    return apiClient.post('/auth/register', {
      username,
      nickname,
    })
  },
}
