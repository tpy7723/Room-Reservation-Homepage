<template>
    <div>
        <h1 italic> 회의실 관리 </h1>
        <button v-show="isLogged && getAuthLevel == '1'" type="button" class="btn btn-outline-primary btn-sm" style="float:right; padding:5px;">
                <router-link to="/Manage_room_add">회의실 등록</router-link>
        </button>
        <br>
        <table class="table table-striped">
            <thead>
                <tr class="text-center">
                    <th class="text-center">회의실 이름</th>
                    <th class="text-center">주말예약 가능 여부</th>
                    <th class="text-center"></th>
                    <th class="text-center"></th>
                </tr>
            </thead>
            <tbody>
                <tr v-for="(item, index) in list" :key="index" style="cursor: pointer">
                    <td>{{item.회의실이름}}</td>
                    <td>{{item.주말예약}}</td>
                    <td>
                        <button v-show="getAuthLevel == '1'" type="button" class="btn btn-primary" @click="call(item)">가능 여부 바꾸기</button>
                    </td>
                    <td>
                        <button v-show="getAuthLevel == '1'" type="button" class="btn btn-primary" @click="deleteReserv(item)">삭제</button>
                    </td>
                </tr>
            </tbody>
        </table>
    </div>
</template>

<script>

export default {
    name: 'Manage_room',
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
        logIn(data) {
            this.$store.commit('logIn', {
                id: this.id,
                authLevel: '1'
            })
        },
        getData: function() {
            
            var url = 'http://localhost:8888/call/room'
            this.$http.get(url)
                .then(result => {
                    if (result.data.status === 'noexist') {
                        console.log('no result')
                        alert("존재하지 않습니다");
                    } else {
                        this.list = result.data.result
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
            var url = 'http://localhost:8888/delete/room'
            console.log(url + `?ID=${item.회의실이름}`)
            this.$http.get(url + `?ID=${item.회의실이름}`)
                .then(result => {
                    console.log(result.data.status)
                })
                .catch(error => {
                    console.log(error)
                })
            this.getData() // 최신화
        },
        call: function(item) {
            var url = 'http://localhost:8888/change/authority' // 승인 바꾸기
            console.log(url + `?id=${item.회의실이름}`)
            this.$http.get(url + `?id=${item.회의실이름}`)
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