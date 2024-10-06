import { createRouter, createWebHistory } from 'vue-router';
import HomeView from '@/views/HomeView.vue';
import LoginView from '@/views/LoginView.vue';
import DashboardView from '@/views/DashboardView.vue';
import CoserView from '@/views/CoserView.vue';
import PhotographerView from '@/views/PhotographerView.vue';
import { useStore } from '@/stores';

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      redirect: '/dashboard',
    },
    {
      path: '/login',
      name: 'login',
      component: LoginView,
    },
    {
      path: '/dashboard',
      name: 'dashboard',
      component: DashboardView,
      children: [
        // {
        //   path: 'coser',
        //   name: 'coser',
        //   component: CoserView,
        // },
        // {
        //   path: 'photographer',
        //   name: 'photographer',
        //   component: PhotographerView,
        // },
      ],
    },
    {
      path: '/about',
      name: 'about',
      // route level code-splitting
      // this generates a separate chunk (About.[hash].js) for this route
      // which is lazy-loaded when the route is visited.
      component: () => import('../views/AboutView.vue'),
    },
  ],
});

router.beforeEach((to, from, next) => {
  const store = useStore();
  const isLoggedIn = store.isLoggedIn;
  if ((to.path === '/dashboard' || to.path.startsWith('/dashboard/')) &&!isLoggedIn) {
    next('/login');
  } else if (to.path === '/login' && isLoggedIn) {
    next('/dashboard');
  } else {
    next();
  }
});

export default router;