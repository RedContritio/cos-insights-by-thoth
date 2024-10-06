<template>
  <div class="login-view" :style="{ backgroundColor: '#ADD8E6' }">
    <el-card class="login-panel" :style="isMobile ? { width: '100%' } : { margin: '0 auto' }">
      <h1 style="text-align: center;">{{ $t('title.thoth_insights') }}</h1>
      <el-form label-position="left" label-width="80px" :model="loginForm" :rules="rules" ref="loginFormRef">
        <el-form-item :label="t('user.username')" prop="username">
          <el-input v-model="loginForm.username" />
        </el-form-item>
        <el-form-item :label="t('user.password')" prop="password">
          <el-input v-model="loginForm.password" type="password" />
        </el-form-item>
        <el-form-item style="text-align: center;">
          <el-button type="primary" @click="handleLogin" style="width: 100%;">{{ $t('button.login') }}</el-button>
        </el-form-item>
      </el-form>
    </el-card>
  </div>
</template>

<script setup lang="ts">
import { reactive, ref, type Ref } from 'vue';
import { useI18n } from 'vue-i18n';
import useStore from '@/stores';
import { ElCard, ElForm, ElFormItem, ElInput, ElButton, type FormInstance } from 'element-plus';
const { t } = useI18n();
const isMobile = window.innerWidth <= 768;
const store = useStore();

const loginForm = reactive({
  username: '',
  password: '',
  });

const rules = {
  username: [
    { required: true, message: t('message.input.username'), trigger: 'blur' },
  ],
  password: [
    { required: true, message: t('message.input.password'), trigger: 'blur' },
  ],
};

const loginFormRef: Ref<FormInstance | null> = ref(null);

const handleLogin = () => {
    const form: FormInstance | null = loginFormRef.value;
    form?.validate((valid) => {
    if (valid) {
      // Placeholder for login logic
      console.log('Logging in with', loginForm.username, loginForm.password);
      store.setLoggedIn(true);
    }
  });
};
</script>

<style scoped>
.login-view {
  height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
}

.login-panel {
  padding: 20px;
  max-width: fit-content;
  border-radius: 8px;
}

.el-form {
  margin-top: 1.5em;
}
</style>