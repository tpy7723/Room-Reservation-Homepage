<template>
    <div id="app">
        <router-view></router-view>
        <header class="header">
            <button type="button" class="btn btn-outline-primary btn-sm" style="float:left; padding:10px;">
            <router-link to="/">홈</router-link>
          </button>
            <div v-show="isLogged">
                <button type="button" class="btn btn-outline-primary btn-sm" style="float:right; padding:5px;" @click.postevent="logOut">
            <router-link to="/">로그아웃</router-link>
          </button>
            </div>
            <div v-show="!isLogged">
                <button type="button" class="btn btn-outline-primary btn-sm" style="float:right; padding:5px;">
              <router-link to="/login">로그인</router-link>
            </button>
            </div>
    
            <br/>
            <ul class="nav justify-content-center">
                <li class="nav-item" v-show="isLogged">
                    <a class="nav-link active">
                        <router-link to="/reservation">예약</router-link>
                    </a>
                </li>
                <li class="nav-item" v-show="isLogged && getAuthLevel == '1' ">
                    <a class="nav-link active">
                        <router-link to="/manage_room">회의실 관리</router-link>
                    </a>
                </li>
            </ul>
        </header>
        <div class="footer">
            연락처 : 010-3017-2440<br/> Made by 박광석<br/>
        </div>
    </div>
</template>

<script>
export default {
    name: 'App',
    data() {
        return {
            msg: 'Welcome to Your Vue.js App'
        }
    },
    computed: {
        isLogged() {
            return this.$store.getters.isLogged
        },
        getAuthLevel() {
            return this.$store.getters.getAuthLevel
        }
    },
    methods: {
        logOut(data) {
            this.$store.commit('logOut', {
                id: '',
                password: ''
            })
        },
    }
}
</script>

<style>
#app {
    font-family: 'Avenir', Helvetica, Arial, sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-align: center;
    color: #2c3e50;
    margin-top: 60px;
}

.header {
    position: fixed;
    left: 0;
    top: 0;
    width: 100%;
    background-color: white;
    color: balck;
    text-align: center;
    border-bottom-style: solid;
    border-bottom-width: 1px;
    margin-bottom: 50px;
    margin-top: 3px;
}

.footer {
    position: fixed;
    left: 0;
    bottom: 0;
    width: 100%;
    background-color: #2c3e50;
    color: white;
    text-align: center;
    margin-top: 30px;
}

.nav-itme {
    color: #42b983;
}
</style>
