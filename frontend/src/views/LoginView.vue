<template>
<AuthView
   title="🌿 Welcome back"
   subtitle="Login EasyToChat"
   button-text="Login"
   link-text="I haven't registered"
   link-to="/register"
   @submit="login"
 >
   <div class="input-group">
     <label for="login-username">Username</label>
     <input id="login-username" v-model="username" type="text" placeholder="Please type username" />
   </div>
   <!--
   <div class="input-group">
     <label for="login-password">Password</label>
     <input id="login-password" v-model="password" type="password" placeholder="Please type password" />
   </div>
   -->
 </AuthView>
 </template>

<script setup lang="ts">
import { chatApi } from '@/api/chatApi'
import { useRouter } from 'vue-router'
import { useUserStore } from '@/stores/user'
import type AuthView from './AuthView.vue'
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

<style scoped></style>
