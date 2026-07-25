<script setup lang="ts">
import { onMounted } from 'vue'

onMounted(async () => {
  const res = await fetch('/api/ping')
  const text = await res.text()
  console.log('Backend response: ', text)
})
</script>

<template>
  <RouterView />
</template>

<style>
body {
  margin: 0;
}
</style>
