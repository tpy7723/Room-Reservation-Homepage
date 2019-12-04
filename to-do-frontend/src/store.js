import Vue from 'vue'
import Vuex from 'vuex'
// import createPersistedState from "vuex-persistedstate"
Vue.use(Vuex)
/* eslint-disable */
export const store = new Vuex.Store({
    state: { // Vuex 의 state 를 이용하여 데이터 관리를 한 곳에서 효율적으로 할 수 있다.
        isLogged: false,
        id: '',
        authLevel: '5', // 사용자 권한
        name: ''
    },
    getters: { // state 값을 받아오기 위한 Getters
        isLogged: function (state) {
            return state.isLogged
        },
        getId: function (state) {
            return state.id
        },
        getAuthLevel: function (state) {
            return state.authLevel
        },
        getName: function (state) {
            return state.name
        }
    },
    mutations: { // state 값을 변경하기 위한 mutations
        logIn: function (state, payload) {  // 로그인
            state.isLogged = true
            state.id = payload.id
            state.name = payload.name
            state.authLevel = payload.authLevel
        },
        logOut: function (state, payload) { // 로그아웃
            state.isLogged = false
            state.id = ''
            state.authLevel = ''
        }
    }
});
