<template lang="html">
    <div class="card">
        <div class="card" style="width: 40rem;">
            <div class="card-body">
                <h3 class="card-title text-left">예약 번호: {{this.num}}</h3>
                <br>
                <p class="card-title text-left">회의 제목 : {{this.title}} </p>
                <p class="card-title text-left">예약 시간 : {{this.start}} ~ {{this.end}}</p>
                <p class="card-title text-left">참석자 : </p>
    
            </div>
            <ul v-for="(item, index) in list" :key="index" class="list-group list-group-flush text-center">
                <li class="list-group-item">
                    <p>{{item.ID}}</p>
                </li>
            </ul>
            <br>
            <button type="submit" class="btn btn-primary" @click.prevent="goBack">       뒤로가기       </button>
    
        </div>
    </div>
</template>

<script>
export default { //후기에 대한 디테일한 수리기록을 보여준다.
    name: "reserv_detail",
    data() {
        return {
            num: '',
            title: '',
            start: new Date(),
            end: new Date(),
            list: []
        }
    },
    computed: {
        isLogged() {
            return this.$store.getters.isLogged
        }
    },
    mounted: function() {
        this.getData()
    },
    methods: {
        goBack: function() {
            this.$router.push("/reservation")
        },
        getData: function() {
            console.log('in reserv_detail')
            this.num = this.$route.query.num
            this.start = this.$route.query.start
            this.end = this.$route.query.end
            this.title = this.$route.query.title

            var url = 'http://localhost:8888/call/participant'
            console.log(url + `?ID=${this.num}`)
            this.$http.get(url + `?ID=${this.num}`) // 예약번호로 요청
                .then(result => {
                    if (result.data.status === 'noexist') {
                        console.log('no result')
                    } else {
                        console.log('get list')
                        console.log(result.data.result)
                        this.list = result.data.result
                    }
                })
                .catch(error => {
                    console.log(error)
                })
        }
    }
}
</script>

<style media="screen">
.card {
    padding: 80px;
    margin-left: auto;
    margin-right: auto;
}
</style>
