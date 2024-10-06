<template>
  <RouterView />
</template>

<script setup lang="ts">
import { ElContainer, ElHeader, ElFooter, ElMain, ElRow, ElCol } from 'element-plus';
import { RouterLink, RouterView } from 'vue-router';
</script>

<style scoped>
.app {
  margin: 0 0;
  width: 100vw;
}
</style>