<template>
    <el-container style="width: 100vw;">
        <el-header>Header</el-header>
        <el-main>
            <el-row>
                <el-col :span="24">
                    <router-link to="/">Home</router-link>
                    <!-- <router-view></router-view> -->
                </el-col>
            </el-row>
        </el-main>
        <el-footer>Footer</el-footer>
    </el-container>
</template>

<script setup lang="ts">

</script>

<style scoped>
.dashboard-view {
    text-align: center;
    margin-top: 50px;
}
</style>