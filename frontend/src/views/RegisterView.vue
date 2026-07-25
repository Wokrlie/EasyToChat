<template>
  <div class="register-container">
    <div class="input-container">
      <div class="tip-label">Username</div>
      <input
        id="username"
        type="text"
        placeholder="Please type some text here"
        v-model="username"
      />
      <div class="tip-label">Nickname</div>
      <input
        id="nickname"
        type="text"
        placeholder="Please type some text here"
        v-model="nickname"
      />
    </div>
    <button class="register-button" @click="register">Register</button>
    <RouterLink to="/login" class="login-link">I have registered</RouterLink>
  </div>
</template>

<script setup lang="ts">
import { chatApi } from '@/api/chatApi'
import { useRouter } from 'vue-router'
import { ref } from 'vue'

const router = useRouter();
const username = ref('')
const nickname = ref('')

const register = async () => {
  try {
    await chatApi.auth_register(username.value, nickname.value);
    router.replace("/login");
  } catch (error) {
    console.error("Register failed", error);
  }
}
</script>

<style scoped>
.register-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  gap: 10px;
  padding: 5px;
  border-radius: 12px;
  height: 100vh;
  width: 100vw;
}

.tip-label {
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

.register-button {
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

.register-button:hover {
  background-color: #7e7e7e;
}

.login-link {
  text-decoration: none;
  color: #9b9a9c;
}
.login-link:hover {
  color: #abaaac;
}
</style>
