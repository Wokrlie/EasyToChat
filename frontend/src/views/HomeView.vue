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
  display: flex;
  flex-direction: column;
  flex: 1;
  gap: 3px;
  height: 100vh;
  overflow: hidden;
}

.tab-bar {
  height: 40px;
  flex-shrink: 0;

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
  flex: 1;

  overflow-y: auto;
  height: 100%;
  border-width: 5px;
  border-color: #aaa;
  border-radius: 12px;
  background-color: #ddd;
}
</style>
