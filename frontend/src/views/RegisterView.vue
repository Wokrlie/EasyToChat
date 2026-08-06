<template>
  <AuthView
  title="Register"
  subtitle="Join EasyToChat"
  button-text="Register"
  line-text="I have registered"
  link-to="/login"
  @submit="register">
    <div class="input-group">
      <label for="register-username">Username</label>
      <input
        id="username"
        type="text"
        placeholder="Please type some text here"
        v-model="username"
      />
    </div>
    <div class="input-group">
      <label for="register-nickname">Nickname</label>
      <input
        id="nickname"
        type="text"
        placeholder="Please type some text here"
        v-model="nickname"
      />
    </div>
    <div class="input-group">
      <label for="register-password">Password</label>
        <input
        id="password"
        type="password"
        placeholder="Please type some text here"
        v-model="password"
        />
    </div>
  </AuthView>
</template>

<script setup lang="ts">
import { chatApi } from '@/api/chatApi'
import { useRouter } from 'vue-router'
import AuthView from './AuthView.vue'
import { ref } from 'vue'

const router = useRouter();

const username = ref('')
const nickname = ref('')
const password = ref('')

const register = async () => {
  try {
    await chatApi.auth_register(username.value, nickname.value, password.value);
    router.replace("/login");
  } catch (error) {
    console.error("Register failed", error);
  }
}
</script>

<style scoped></style>
