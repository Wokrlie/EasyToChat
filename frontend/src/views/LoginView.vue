<template>
  <div class="login-container">
    <div class="input-container">
      <div class="username-label">Username</div>
      <input
        id="username"
        type="text"
        placeholder="Please type some text here"
        v-model="username"
      />
    </div>
    <button class="login-button" type="submit" @click="login">Login</button>
    <RouterLink to="/register" class="register-link"> I haven't registered </RouterLink>
  </div>
</template>

<script setup lang="ts">
import { chatApi } from '@/api/chatApi'
import { useRouter } from 'vue-router'
import { useUserStore } from '@/stores/user'
import { ref } from 'vue'

const router = useRouter()
const userStore = useUserStore()

const username = ref('')

const login = async () => {
  try {
    const response = await chatApi.auth_login(username.value)
    const data = response.data
    userStore.login(data.nickname, data.username)
    console.log("User's nickname: ", data.nickname)
    router.replace('/')
  } catch (error) {
    console.error('Login failed', error)
  }
}
</script>

<style scoped>
.login-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  gap: 10px;
  padding: 5px;
  border-radius: 12px;
  width: 100vw;
  height: 100vh;
}

.username-label {
  font-family: system-ui, monospace;
  font-size: 20px;
}

.input-container {
  display: flex;
  flex-direction: column;
  gap: 10px;
  width: 20%;
}

input {
  border: 2px solid #ccc;
  padding: 12px 16px;
  border-radius: 8px;
  font-size: 16px;
}

.login-button {
  height: 60px;
  width: 100px;
  border-radius: 12px;
  border-width: 0px;
  background-color: #777;
  transition: background-color 0.2s;
  box-shadow: 4px 3px 4px;
  font-size: 20px;
  cursor: pointer;
}

.login-button:hover {
  background-color: #7e7e7e;
}

.register-link {
  text-decoration: none;
  color: #9b9a9c;
}
.register-link:hover {
  color: #abaaac;
}
</style>
