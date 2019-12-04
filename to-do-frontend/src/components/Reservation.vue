<template>
    <div>
        <h1 italic> 예약게시판 </h1>
        <button v-show="isLogged && getAuthLevel == '0'" type="button" class="btn btn-outline-primary btn-sm" style="float:right; padding:5px;">
                <router-link to="/reserv_add">예약등록</router-link>
        </button>
        <br>
        <table class="table table-striped">
            <thead>
                <tr class="text-center">
                    <th class="text-center">예약 번호</th>
                    <th class="text-center">회의실 이름</th>
                    <th class="text-center">예약자 ID</th>
                    <th class="text-center">회의 제목</th>
                    <th class="text-center">From</th>
                    <th class="text-center">To</th>
                    <th class="text-center">예약 승인</th>
                    <th class="text-center"></th>
                </tr>
            </thead>
            <tbody>
                <tr v-for="(item, index) in list" :key="index" style="cursor: pointer">
                    <td @click="readBoard(item)">{{item.예약번호}}</td>
                    <td @click="readBoard(item)">{{item.회의실이름}}</td>
                    <td @click="readBoard(item)">{{item.ID}}</td>
                    <td @click="readBoard(item)">{{item.회의제목}}</td>
                    <td @click="readBoard(item)">{{item.시작시간}}</td>
                    <td @click="readBoard(item)">{{item.끝시간}}</td>
                    <td @click="readBoard(item)">{{item.예약승인}}</td>
                    <td>
                        <button v-show="getId == item.ID" type="button" class="btn btn-primary" @click="deleteReserv(item)">삭제</button>
                        <button v-show="getAuthLevel == '1'" type="button" class="btn btn-primary" @click="call(item)">승인</button>
                    </td>
                </tr>
            </tbody>
        </table>
    </div>
</template>

<script>
export default {
    name: 'Login',
    data() {
        return {
            list: [],
            msg: '',
        }
    },
    mounted: function() {
        this.getData()
    },
    computed: {
        isLogged() {
            return this.$store.getters.isLogged
        },
        getId() {
            return this.$store.getters.getId
        },
        getAuthLevel() {
            return this.$store.getters.getAuthLevel
        }
    },
    methods: {
        readBoard: function(item) {
            // this.$router.push("/reserv_detail")
            console.log('readBoard 함수 콜')
            console.log(item)
            this.$router.push({
                name: 'reserv_detail',
                query: {
                    start: item.시작시간,
                    end: item.끝시간,
                    title: item.회의제목,
                    num: item.예약번호
                }
            })
        },
        logIn(data) {
            this.$store.commit('logIn', {
                id: this.id,
                authLevel: '1'
            })
        },
        getData: function() {
            var url = 'http://localhost:8888/call/reservation'
            this.$http.get(url + `?ID=${this.getId}`)
                .then(result => {
                    if (result.data.status === 'noexist') {
                        console.log('no result')
                        alert("존재하지 않습니다");
                    } else {
                        this.list = result.data.result
                        this.list.forEach(v => {
                            v.시작시간 = this.$moment(v.시작시간).tz('Asia/Seoul').format('YYYY.MM.DD HH:mm')
                            v.끝시간 = this.$moment(v.끝시간).tz('Asia/Seoul').format('YYYY.MM.DD HH:mm')
                        })
                    }
                })
                .catch(error => {
                    console.log(error)
                })
        },
        goBack: function() {
            this.$router.push("/")
        },
        createLog: function() {
            this.$router.push("/reserv_add")
        },
        deleteReserv: function(item) {
            var url = 'http://localhost:8888/delete/reservation'
            console.log(url + `?ID=${item.예약번호}`)
            this.$http.get(url + `?ID=${item.예약번호}`)
                .then(result => {
                    console.log(result.data.status)
                })
                .catch(error => {
                    console.log(error)
                })
            this.getData() // 최신화
        },
        call: function(item) {
            var url = 'http://localhost:8888/call/reserv_em'
            console.log(url + `?id=${item.예약번호}`)
            this.$http.get(url + `?id=${item.예약번호}`)
                .then(result => {
                    console.log(result.data.status)
                })
                .catch(error => {
                    console.log(error)
                })
            this.getData()
        }
    }
}
</script>

<style>
table {
    width: 100%;
    border-collapse: collapse;
}

table th {
    font-size: 1.2rem;
}

table tr {
    height: 2rem;
    text-align: center;
    border-bottom: 1px solid #505050;
}

table tr:first-of-type {
    border-top: 2px solid #404040;
}

table tr td {
    padding: 1rem 0;
    font-size: 1.1rem;
}

.btn-cover {
    margin-top: 1.5rem;
    text-align: center;
}

.btn-cover .page-btn {
    width: 5rem;
    height: 2rem;
    letter-spacing: 0.5px;
}

.btn-cover .page-count {
    padding: 0 1rem;
}
</style>