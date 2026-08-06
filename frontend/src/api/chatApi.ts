import axios from 'axios'
import { useUserStore } from '@/stores/user'
import type { Message } from '@/types/message'
import type { Gender, User } from '@/types/user'

const apiClient = axios.create({
  baseURL: '/api',
  timeout: 5000,
})

apiClient.interceptors.request.use(
  (config) => {
    const userStore = useUserStore()
    const whiteList = ['/auth/login', '/auth/register']
    if (whiteList.some((path) => config.url?.includes(path))) {
      return config
    }
    const token = userStore.token
    if (token) config.headers.Authorization = `Bearer ${token}`
    return config
  },
  (error) => Promise.reject(error),
)

export const chatApi = {
  getMessages() {
    return apiClient.get<Message[]>('/messages')
  },
  sendMessage(content: string, senderName: string = 'User', token: string) {
    return apiClient.post('/messages', {
      content,
      sender_type: 'user',
      sender_name: senderName,
      token: token,
    })
  },
  auth_login(username: string, password: string) {
    return apiClient.post('/auth/login', { username, password })
  },
  auth_register(username: string, nickname: string, password: string, gender?: Gender) {
    const payload: User = { username, nickname, password }
    if (gender !== undefined) payload.gender = gender
    return apiClient.post('/auth/register', payload)
  },
}
