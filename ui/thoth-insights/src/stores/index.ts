import { defineStore } from 'pinia';
import { Project, User, type ProjectID, type TimeStamp } from "@/types";

export const useStore = defineStore('login', {
  state: () => ({
    isLoggedIn: false,
    loggedInUser: null as User | null,
    expirationTime: null as TimeStamp | null,
    projects: [] as Project[], // 这里假设项目的数据结构暂不确定，你可以根据实际情况调整类型
  }),
  actions: {
    setLoggedIn(loggedIn: boolean) {
      this.isLoggedIn = loggedIn;
    },
    setLoggedInUser(user: User) {
      this.loggedInUser = user;
    },
    setExpirationTime(time: TimeStamp) {
      this.expirationTime = time;
    },
    addProject(project: Project) {
      this.projects.push(project);
    },
    removeProject(projectId: ProjectID) {
      this.projects = this.projects.filter(project => project.id!== projectId);
    },
  },
});

export default useStore;