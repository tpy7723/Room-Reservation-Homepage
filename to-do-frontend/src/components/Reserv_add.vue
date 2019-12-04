<template>
    <body>
        <form name="registerForm">
            <div class="reserv_add">
                <h1 italic> 예약 등록 </h1>
                <div>
                    <label>회의실</label>
                </div>
                <select name='room'>
                    <option value='' selected>-- 선택 --</option>
                    <option v-for="(item, index) in list" :key="index">
                      {{item.회의실이름}}
                    </option>
                </select>
                <div>
                    <label>회의 제목</label>
                </div>
                <div>
                    <input type="text" class="form-control" id='TITLE' v-model="TITLE" placeholder="제목을 입력해주세요">
                </div>
                <div>
                    <label>시작 시간</label>
                </div>
                <div id="starttime">
                    <DateTimePicker v-model="startDate" :options="options"></DateTimePicker>
                </div>
                <div>
                    <label>끝 시간</label>
                </div>
                <div id="endtime">
                    <DateTimePicker v-model="endDate" :options="options"></DateTimePicker>
                </div>
                <div>
                    <label>참가자 추가: {{userList}}</label>
                </div>
                <div>
                    <input v-model="userName">
                    <button class="btn btn-primary" @click.prevent="addUser">추가</button>
                    <button class="btn btn-primary" @click.prevent="removeUser">삭제</button>
                </div>
    
                <button type="submit" class="btn btn-primary" @click.prevent="goBack">뒤로가기</button>
                <button type="submit" class="btn btn-primary" @click.prevent="submitLog">예약</button>
            </div>
        </form>
    </body>
</template>

<script>
import { Datetime } from 'vue-datetime'
export default {
    name: "reservation_add",
    data() {
        return {
            list: [],
            day: '',
            TITLE: '',
            loc: '',
            userName: '',
            userList: [],
            date: new Date(),
            startDate: new Date(),
            endDate: new Date(),
            options: {
                // defaults
                timeFormat: {
                    locale: "ko",
                    weekday: "short",
                    year: "numeric",
                    month: "short",
                    day: "numeric",
                    hour: "numeric",
                    minute: "numeric",
                    hour12: true
                },
                display: {
                    maxWidth: 30
                }
            }
        };
    },
    computed: {
        getId() {
            return this.$store.getters.getId
        }
    },
    mounted: function() {
        this.getData()
    },
    methods: {
        getData: function() {
            console.log("get data 함수 콜")
            var url = 'http://localhost:8888/call/room'
            this.$http.get(url)
                .then(result => {
                    if (result.data.status === 'noexist') {
                        console.log('no result')
                        alert("사용자가 존재하지 않습니다");
                    } else {
                        this.list = result.data.result
                    }
                })
                .catch(error => {
                    console.log(error)
                })
        },
        removeUser: function() {
            if (this.userList.indexOf(this.userName) == -1) { // 없는 경우
                alert("해당 참석자는 목록에 없습니다.");
                this.userName = ''
                return
            } else {
                this.userList.splice(this.userList.indexOf(this.userName), 1)
                alert("해당 참석자를 삭제 했습니다.");
                this.userName = ''
                return
            }
            return
        },
        addUser: function() {
            if (this.userList.indexOf(this.userName) != -1) { // 이미 입력된 경우
                alert("이미 추가하셨습니다.");
                this.userName = ''
                return
            }
            console.log("addUser 함수 콜")
            console.log(this.userName)
            var temp = this.userName
            var url = 'http://localhost:8888' + `/find?id=${temp}`;
            this.$http.get(url)
                .then(result => {
                    if (result.data.status === 'noexist') {
                        console.log('no result')
                        alert("존재하지 않습니다");
                    } else {
                        console.log(temp)
                        alert("참가자가 추가되었습니다");
                        this.userList.push(temp)
                    }
                })
                .catch(error => {
                    console.log(error)
                })
            this.userName = ''
            return
        },
        goBack: function() {
            this.$router.push("reservation")
        },
        submitLog: function() { // 예약 버튼
            var Room_ = registerForm.room.value;
            var Title_ = registerForm.TITLE.value;
            var Start_ = this.$moment(this.startDate);
            var End_ = this.$moment(this.endDate);
            var Id_ = this.getId; // 로그인한 아이디
            console.log('id= ' + Id_);
            if (Start_.isAfter(End_)) {
                alert('마감시간이 시작시간보다 뒤에 있어야 합니다');
                return;
            }
            console.log(Start_.minute())
            console.log(End_.minute())
            if(Start_.minute() != "30" && Start_.minute() != "0" && End_.minute() != "30" && End_.minute() != "0"){
              alert("예약 시간을 30분 단위로 설정해주세요"); return;
            }

            Start_ = this.$moment(this.Start_).tz('Asia/Seoul').format('YYYY-MM-DD HH:mm')
            End_ = this.$moment(this.End_).tz('Asia/Seoul').format('YYYY-MM-DD HH:mm')

            
            if (Room_ == "") { alert("회의실을 입력해주세요"); return; }
            if (Title_ == "") { alert("회의 제목을 입력해주세요"); return; }
            if (Start_ == "") { alert("시작 시간을 입력해주세요"); return; }
            if (End_ == "") { alert("끝 시간을 입력해주세요"); return; }

            var url = 'http://localhost:8888' + `/request/reservation?title=${Title_}&start=${Start_}&end=${End_}&id=${Id_}&room=${Room_}`;
            console.log(url)
            this.$http.get(url)
                .then((result) => {
                    consolea.log(result)
                    if (result.data.status == 'success') { // 로그인 성공
                        console.log('success')
                    } else {
                        console.log('error')
                        alert("중복된 데이터가 있습니다!");
                        return
                    }
                })
                .catch((error) => {
                    console.log(error)
                    console.log('server error')
                })

            for (var i = 0; i < this.userList.length; i++) {
                var url = 'http://localhost:8888' + `/add/participant?id=${this.userList[i]}`;
                console.log("참석자 입력")
                console.log(url)
                this.$http.get(url)
                    .then((result) => {
                        console.log(result)
                        if (result.data.status == 'success') {
                            console.log('success')
                            // this.$router.push("reservation")
                        } else {
                            console.log('error')
                        }
                    })
                    .catch((error) => {
                        console.log(error)
                        console.log('server error')
                    })
            }
            alert("성공적으로 예약되었습니다!");
            this.$router.push("reservation")
        }
    }

}
</script>

<style media="screen">
.reserv_add {
    width: 25%;
    padding-top: 20px;
    margin-left: auto;
    margin-right: auto;
    text-align: center;
}
</style>
