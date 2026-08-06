<template>
  <AuthView
  title="Register"
  subtitle="Join EasyToChat"
  button-text="Register"
  line-text="I have registered"
  link-to="/login"
  @submit="register">
    <div class="input-group">
      <div class="tip-label">Username</div>
      <input
        id="username"
        type="text"
        placeholder="Please type some text here"
        v-model="username"
      />
    </div>
    <div class="input-group">
      <div class="tip-label">Nickname</div>
      <input
        id="nickname"
        type="text"
        placeholder="Please type some text here"
        v-model="nickname"
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

const register = async () => {
  try {
    await chatApi.auth_register(username.value, nickname.value);
    router.replace("/login");
  } catch (error) {
    console.error("Register failed", error);
  }
}
</script>

<style scoped></style>
