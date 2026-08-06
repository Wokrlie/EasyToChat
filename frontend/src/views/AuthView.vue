<!-- components/AuthForm.vue -->
<template>
  <div class="auth-container">
    <div class="auth-card">
      <h1 class="auth-title">{{ title }}</h1>
      <p class="auth-subtitle">{{ subtitle }}</p>

      <!-- 父组件通过插槽传入输入框等 -->
      <div class="auth-fields">
        <slot></slot>
      </div>

      <button class="auth-button" @click="$emit('submit')">
        {{ buttonText }}
      </button>

      <router-link to="linkTo" class="auth-link">
        {{ linkText }}
      </router-link>
    </div>
  </div>
</template>

<script setup lang=ts>
defineProps({
  title: String,
  subtitle: String,
  buttonText: String,
  linkText: String,
  linkTo: String,
});
defineEmits(['submit']);
</script>

<style scoped>
/* 卡片容器 */
.auth-container {
  display: flex;
  align-items: center;
  justify-content: center;
  min-height: 100vh;
  background: linear-gradient(145deg, #e8f5e9 0%, #c8e6c9 100%);
  font-family: system-ui, -apple-system, 'Segoe UI', Roboto, sans-serif;
  padding: 20px;
}

/* 卡片本身 */
.auth-card {
  background: rgba(255, 255, 255, 0.85);
  backdrop-filter: blur(8px);
  -webkit-backdrop-filter: blur(8px);
  border-radius: 32px;
  padding: 48px 40px;
  width: 100%;
  max-width: 400px;
  box-shadow: 0 12px 40px rgba(76, 175, 80, 0.15);
  border: 1px solid rgba(255, 255, 255, 0.6);
}

.auth-title {
  text-align: center;
  font-size: 28px;
  font-weight: 600;
  color: #2e7d32;
  margin-bottom: 6px;
  letter-spacing: -0.3px;
}

.auth-subtitle {
  text-align: center;
  font-size: 15px;
  color: #558b2f;
  margin-bottom: 32px;
}

/* 输入框区域，让父组件的 .input-group 生效 */
.auth-fields {
  display: flex;
  flex-direction: column;
  gap: 20px;
  margin-bottom: 8px;
}

/* 为了让父组件插槽内的输入框应用样式，我们使用 :deep() */
.auth-fields :deep(.input-group) {
  display: flex;
  flex-direction: column;
  gap: 6px;
}

.auth-fields :deep(.input-group label) {
  font-size: 13px;
  font-weight: 500;
  color: #2e7d32;
}

.auth-fields :deep(.input-group input) {
  padding: 14px 16px;
  border-radius: 12px;
  border: 2px solid #c8e6c9;
  font-size: 16px;
  outline: none;
  transition: all 0.25s ease;
  background: #fafffe;
}

.auth-fields :deep(.input-group input:focus) {
  border-color: #4caf50;
  box-shadow: 0 0 0 4px rgba(76, 175, 80, 0.15);
  background: white;
}

.auth-fields :deep(.input-group input::placeholder) {
  color: #a5d6a7;
}

/* 按钮 */
.auth-button {
  width: 100%;
  padding: 16px;
  border: none;
  border-radius: 12px;
  background: #4caf50;
  color: white;
  font-size: 18px;
  font-weight: 600;
  cursor: pointer;
  transition: all 0.2s ease;
  margin-top: 8px;
  box-shadow: 0 4px 8px rgba(76, 175, 80, 0.2);
}
.auth-button:hover {
  background: #43a047;
  transform: translateY(-2px);
  box-shadow: 0 8px 16px rgba(76, 175, 80, 0.3);
}
.auth-button:active {
  transform: translateY(0);
}

/* 底部链接 */
.auth-link {
  display: block;
  text-align: center;
  margin-top: 24px;
  color: #66bb6a;
  font-size: 14px;
  text-decoration: none;
  transition: color 0.2s;
}
.auth-link:hover {
  color: #2e7d32;
  text-decoration: underline;
}

@media (max-width: 480px) {
  .auth-card {
    padding: 32px 20px;
  }
}
</style>
