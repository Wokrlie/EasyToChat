import axios from 'axios'
import { useUserStore } from '@/stores/user'
import type { Message } from '@/types/message'
import type { Gender, User } from '@/types/user'
import type { Conver } from '@/types/Conver'

const apiClient = axios.create({
  baseURL: '/api',
  timeout: 5000,
})

apiClient.interceptors.request.use(
  (config) => {
    const userStore = useUserStore()
    const whiteList = ['ping', '/auth/login', '/auth/register']
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
  ping() {
    return apiClient.get('/ping')
  },
  auth_login(username: string, password: string) {
    return apiClient.post('/auth/login', { username, password })
  },
  auth_register(username: string, nickname: string, password: string, gender?: Gender) {
    const payload: User = { username, nickname, password }
    if (gender !== undefined) payload.gender = gender
    return apiClient.post('/auth/register', payload)
  },
  getMessages(conver_id: string) {
    return apiClient.get<Message[]>('/messages', { params: { conver_id } })
  },
  sendMessage(conver_id: string, content: string, senderName: string = 'User', token: string) {
    return apiClient.post('/messages', {
      conver_id,
      content,
      sender_type: 'user',
      sender_name: senderName,
      token: token,
    })
  },
  createConver(name: string, usernames: string[]) {
    return apiClient.post('/convers/create', { name, usernames })
  },
  destroyConver(id: string) {
    return apiClient.post('/convers/destory', { id })
  },
  getConvers() {
    return apiClient.get<Conver[]>('/convers')
  },
}
