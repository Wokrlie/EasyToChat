<template>
<div class="home-container">
  <draggable
  v-model="tabs"
  item-key="name"
  class="tab-bar"
  :animation="200"
  >
    <template #item="{ element: tab }">
    <RouterLink
    :to="tab.path"
    class="tab"
    activeClass="active"
    >
      {{ tab.label }}
    </RouterLink>
    </template>
  </draggable>
  <div class="content">
    <RouterView />
  </div>
</div>
</template>

<script setup lang="ts">
import draggable from 'vuedraggable';
import { ref } from 'vue';

const tabs = ref([
  { name: "chat", label: "Chat", path: "/chat" },
  { name: "settings", label: "Settings", path: "/settings"}
])

</script>

<style scoped>
.home-container {
  display: grid;
  gap: 3px;
  grid-template-rows: auto 1fr;
  height: 100vh;
}

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
  border-radius: 12px;

  background-color: #eaeaea;
  color: black;
  text-decoration: none;
  font-family: system-ui, monospace;
  cursor: pointer;

  transition: background-color 300ms;
}

.tab:hover {
  background-color: #e0e0e0;
}

.content {
  overflow-y: auto;
  height: 100vh;
  border-width: 5px;
  border-color: #aaa;
  border-radius: 12px;
  background-color: #ddd;
}
</style>
