<template>
 <div class="home-container">
   <div class="tab-bar">
     <div
      v-for="tab in tabs"
      :key="tab.name"
      class="tab"
      :class="{ active: currentTab === tab.name }"
      @click="currentTab = tab.name"
      >
        {{tab.label}}
      </div>
   </div>
 </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'

const tabs = [
  { name: "chat", label: "Chat" },
  { name: "settings", label: "Settings"}
]

const currentTab = ref('chat');
</script>

<style scoped>
.tab-bar {
  display: flex;
  gap: 4px;
}

.tab {
  display: flex;

  width: 200px;
  height: 40px;
  align-items: center;
  text-align: center;
  justify-content: center;
  border-radius: 12px 12px 0 0;

  background-color: #eaeaea;
  box-shadow:  10px 5px 5px #000;
  font-family: system-ui, monospace;
}

.tab:hover {
  background-color: #e1e1e1;
}
</style>
