<template>
    <div class="hello">
        <img src="../assets/logo.png" alt="Vue.js PWA">
        <h2 v-show="!isLogged"> 방문해 주셔서 감사합니다.<br/></h2>
        <h3 v-show="isLogged"> {{ID}}님 안녕하세요~</h3>
    </div>
</template>

<script>
export default {
    name: 'hello',
    data() {
        return {
            msg: '회의실 예약 시스템',
            Log: this.$store.getters.isLogged,
            ID: this.$store.getters.getId,
        }
    },
    mounted: function() {
        this.getData()
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
        getData: function() {
            this.ID = this.$store.getters.getId
        }
    }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style>
#app {
    text-align: center;
    color: #2c3e50;
    margin-top: 100px;
}

h1,
h2 {
    font-weight: normal;
}

ul {
    list-style-type: none;
    padding: 0;
}

li {
    display: inline-block;
    margin: 0 10px;
}

a {
    color: #35495E;
}
</style>
