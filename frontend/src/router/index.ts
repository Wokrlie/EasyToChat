import { createRouter, createWebHistory } from 'vue-router'
import { useUserStore } from '@/stores/user'

import HomeView from '@/views/HomeView.vue'
import ChatView from '@/views/ChatView.vue'
import SettingsView from '@/views/SettingsView.vue'
import LoginView from '@/views/LoginView.vue'
import RegisterView from '@/views/RegisterView.vue'

const routes = [
  {
    path: '/',
    component: HomeView,
    children: [
      {
        path: '',
        component: ChatView,
      },
      {
        path: 'chat',
        component: ChatView,
      },
      {
        path: 'settings',
        component: SettingsView,
      },
    ],
  },
  {
    path: '/login',
    component: LoginView,
  },
  {
    path: '/register',
    component: RegisterView,
  },
]

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: routes,
})

router.beforeEach((to, from, next) => {
  const userStore = useUserStore()
  const isLoggedIn = userStore.isLoggedIn
  if (to.meta.requireAuth && !isLoggedIn) {
    next('/login')
  } else {
    next()
  }
})

export default router
