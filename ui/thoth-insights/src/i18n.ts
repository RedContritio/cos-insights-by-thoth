import { createI18n } from 'vue-i18n'

export const i18n = createI18n({
  locale: 'zh',
  fallbackLocale: 'en',
  messages: {
    en: {
      user: {
        username: 'Username',
        password: 'Password',
      },
      button: {
        login: 'Login',
      },
      message: {
        input: {
            username: 'Please input username',
            password: 'Please input password',
        },
        hello: 'hello world'
      },
      title: {
        thoth_insights: 'Thoth Insights',
        login: 'Login'
      }
    },
    zh: {
        user: {
            username: '用户名',
            password: '密码',
        },
        button: {
            login: '登录',
        },
        message: {
            input: {
                username: '请输入用户名',
                password: '请输入密码',
            },
            hello: '你好，世界'
        },
        title: {
            thoth_insights: '托特洞察',
            login: '登录'
        }
    },
    ja: {
      message: {
        hello: 'こんにちは、世界'
      }
    }
  }
})

export default i18n;