<template>
    <div class="login2">
        <h1 italic> 회원가입 </h1>
        <form name="registerForm" action="register_ok.asp" method="post">
            <div>
                <div>
                    <label for="LoginID">ID</label>
                </div>
                <div>
                    <input type="text" class="form-control" id='LoginID' v-model="LoginID" placeholder="LoginID">
                </div>
                <div>
                    <label for="password">Password</label>
                </div>
                <div>
                    <input type="password" class="form-control" id='password' v-model="password" placeholder="Password">
                </div>
                <div>
                    <label for="Password">Re-Password</label>
                </div>
                <div>
                    <input type="password" class="form-control" id='pw_ok' placeholder="Re-Password">
                </div>
                <div>
                    <label for="Name">Name</label>
                </div>
                <div>
                    <input type="text" class="form-control" id='name' v-model="Name" placeholder="홍길동">
                </div>
                <div>
                    <label for="email">Email</label>
                </div>
                <div>
                    <input type="text" class="form-control" id='email' v-model="email" placeholder="tpy7723@naver.com">
                </div>
                <br>
    
                <br>
                <button type="submit" class="btn btn-primary" @click.prevent="goBack">       뒤로가기       </button>
                <button type="submit" class="btn btn-primary" @click.prevent="submit">       제출       </button>
            </div>
        </form>
    </div>
</template>


<script>
export default {
    name: 'join',
    data() {
        return {
            LoginID: '',
            Password: '',
            Name: '',
            Email: ''
        }
    },
    computed: {
        isLogged() {
            return this.$store.getters.isLogged
        }
    },
    methods: {
        goBack: function() {
            this.$router.push("/login")
        },
        submit: function() {
            var regex;
            var LoginID = registerForm.LoginID.value;
            var Loginpassword = registerForm.password.value;
            var pw_ok = registerForm.pw_ok.value;
            var name = registerForm.name.value;
            var email = registerForm.email.value;
            if (LoginID == "") { alert("ID를 입력해주세요"); return; }
            if (Loginpassword == "") { alert("Password를 입력해주세요"); return; }
            if (pw_ok == "") { alert("Re-Password을 입력해주세요"); return; }
            if (name == "") { alert("Name을 입력해주세요"); return; }
            if (email == "") { alert("Email을 입력해주세요"); return; }
            if (Loginpassword != pw_ok) { alert("비밀번호와 비밀번호 확인이 다릅니다"); return; }
            // regex=/^(01[016789]{1}|02|0[3-9]{1}[0-9]{1})-?[0-9]{3,4}-?[0-9]{4}$/; // 휴대전화
            regex = /^[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*@[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*.[a-zA-Z]{2,3}$/i; // 이메일
            if (regex.test(email) === false) {
                alert("잘못된 이메일 형식입니다.");
                return;
            }
            var url = 'http://localhost:8888' + `/join?id=${LoginID}&pw=${Loginpassword}&name=${name}&email=${email}`;
            console.log(url)
            this.$http.get(url)
                .then((result) => {
                    console.log(result)
                    if (result.data.status == 'success') { // 로그인 성공
                        console.log('success')
                        alert("성공적으로 가입되었습니다! 로그인 해주세요~");
                        this.$router.push("/")
                    } else {
                        console.log('error')
                        alert("중복된 데이터가 있습니다!");
                        this.$notice({
                            type: 'alert',
                            text: '로그인 정보가 올바르지 않습니다'
                        })
                    }
                })
                .catch((error) => {
                    console.log(error)
                    console.log('server error')
                })
        }
    }
}
</script>


<style>
.login2 {
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
