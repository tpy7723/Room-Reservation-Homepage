import Vue from 'vue'
import Vuex from 'vuex'
import createPersistedState from "vuex-persistedstate"
Vue.use(Vuex)
/* eslint-disable */
export const store = new Vuex.Store({
    state: {
        isLogged: false,
        id: '',
        authLevel: '5'
    },
    getters: {
        isLogged: function (state) {
            return state.isLogged
        },
        getId: function (state) {
            return state.id
        },
        getAuthLevel: function (state) {
            return state.authLevel
        }
    },
    mutations: {
        logIn: function (state, payload) {
            state.isLogged = true
            state.id = payload.id
            state.authLevel = payload.authLevel
        },
        logOut: function (state, payload) {
            state.isLogged = false
            state.id = ''
            state.authLevel = ''
        }
    }
});
