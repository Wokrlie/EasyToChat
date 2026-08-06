import { defineStore } from 'pinia'
import { ref } from 'vue'

export const useUserStore = defineStore(
  'user',
  () => {
    const isLoggedIn = ref(false)
    const nickname = ref('')
    const username = ref('')
    function login(userNickname: string, userName: string) {
      nickname.value = userNickname
      username.value = userName
      isLoggedIn.value = true
    }
    function logout() {
      nickname.value = ''
      username.value = ''
      isLoggedIn.value = false
    }
    return { isLoggedIn, nickname, username, login, logout }
  },
  {
    persist: {
      key: 'user-store',
      storage: sessionStorage,
      pick: ['nickname', 'isLoggedIn', 'username'],
    },
  },
)
