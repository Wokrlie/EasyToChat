import { defineStore } from 'pinia'
import { ref } from 'vue'

export const useUserStore = defineStore(
  'user',
  () => {
    const isLoggedIn = ref(false)
    const nickname = ref('')
    const username_ = ref('')
    function login(userNickname: string, username: string) {
      nickname.value = userNickname
      username_.value = username
      isLoggedIn.value = true
    }

    function logout() {
      nickname.value = ''
      isLoggedIn.value = false
    }
    return { isLoggedIn, nickname, username_, login, logout }
  },
  {
    persist: {
      key: 'user-store',
      pick: ['nickname', 'isLoggedIn'],
    },
  },
)
