<template>
    <div class="login">
        <h1 italic> 로그인 </h1>
        <div>
            <label for="id">회원 ID</label>
        </div>
        <div>
            <input type="text" class="form-control" id="id" placeholder="ID" v-model="id">
        </div>
        <br>
    
        <div>
            <label for="password">비밀번호</label>
        </div>
    
        <div>
            <input type="password" class="form-control" id="password" placeholder="Password" v-model="password">
        </div>
        <br>
    
        <div>
            <button class="btn btn-primary" @click.prevent="submit">로그인</button>
            <button type="submit" class="btn btn-primary" @click.prevent="goJoin">       회원가입       </button>
        </div>
        <br>
    </div>
</template>

<script>
export default {
    name: 'login',
    data() {
        return {
            msg: 'Welcome to Your Vue.js App',
            id: '',
            password: ''
        }
    },
    computed: {
        isLogged() {
            return this.$store.getters.isLogged
        }
    },
    methods: {
        goJoin: function() {
            this.$router.push("/join")
        },
        logIn(data) {
            this.$store.commit('logIn', {
                id: data.ID,
                name: data.이름,
                authLevel: data.권한
            })
        },
        submit: function() {
            var url = 'http://localhost:8888/login';
            console.log("id는 " + this.id)
            console.log("pw는 " + this.password)

            this.$http.get(url + `?id=${this.id}&password=${this.password}`)
                .then((result) => {
                    if (result.data.status == 'success') { // 로그인 성공
                        console.log('로그인 성공')
                        this.logIn(result.data.result[0])
                        this.$router.push("/")
                    } else if (result.data.status == 'no-user') {
                        console.log("no user")
                        alert('존재하지 않는 사용자입니다.')
                    } else if (result.data.status == 'incorrect') {
                        console.log("incorrect")
                        alert('비밀번호가 일치하지 않습니다')
                    } else {
                        console.log('error')
                        alert('서버에러입니다.')
                    }
                })
                .catch((error) => {
                    console.log('server error')
                })
        }
    }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style>
.login {
    width: 25%;
    padding-top: 10px;
    margin-left: auto;
    margin-right: auto;
    text-align: center;
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
