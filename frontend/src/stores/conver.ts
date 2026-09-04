import type { User } from '@/types/user'
import { defineStore } from 'pinia'
import { ref } from 'vue'

export const useConverStore = defineStore(
  'conver',
  () => {
    const converID = ref('')
    const converName = ref('')
    const users = ref<User[]>()

    function enter(user: User) {
      users.value?.push(user)
    }
    function leave(targetUser: User) {
      users.value = users.value?.filter((user) => user.username != targetUser.username)
    }
    return {
      converID,
      converName,
      enter,
      leave,
    }
  },
  {
    persist: {
      key: 'conver-store',
      storage: sessionStorage,
      pick: ['converID', 'converName', 'users'],
    },
  },
)
