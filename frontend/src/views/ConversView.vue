<template>
<div class="convers-container">
  <el-input class="search-bar" @keydown.enter="searchConver" v-model="searchText"/>
  <draggable
  v-model="convers"
  item-key="id"
  :animation="200"
  class="convers"
  >
    <template #item="{ element: conver }">
    <RouterLink :to="conver.path" class="conver" activeClass="active">
      {{ conver.name }}
    </RouterLink>
    </template>
  </draggable>
</div>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import { RouterLink } from 'vue-router';
import type draggable from 'vuedraggable';

const convers = ref([])
const searchText = ref('')

const searchConver = () => { }
</script>
