import { createRouter, createWebHistory } from 'vue-router'

import HomeView from '@/views/HomeView.vue'
import ChatView from '@/views/ChatView.vue'
import SettingsView from '@/views/SettingsView.vue'

const routes = [
  {
    path: '/',
    component: HomeView,
    children: [
      {
        path: '',
        component: ChatView
      },
      {
        path: 'chat',
        component: ChatView
      },
      {
        path: 'settings',
        component: SettingsView
      }
    ]
  },
]

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: routes,
})

export default router
