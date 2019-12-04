<template>
    <body>
        <form name="registerForm">
            <div class="reserv_add">
                <h1 italic> 회의실 등록 </h1>
                <div>
                    <label>회의실 이름</label>
                </div>
                <div>
                    <input type="text" class="form-control" id='TITLE' v-model="TITLE" placeholder="제목을 입력해주세요">
                </div>
                <br>
                <div>
                    <label>주말 예약 가능 여부</label>
                </div>
                <select name='possible'>
                    <option value='' selected>-- 선택 --</option>
                    <option value='1'> 가능 </option>
                    <option value='0'> 불가능 </option>
                </select>
                <br><br><br><br>
                <button type="submit" class="btn btn-primary" @click.prevent="goBack">뒤로가기</button>
                <button type="submit" class="btn btn-primary" @click.prevent="submitLog">등록</button>
            </div>
        </form>
    </body>
</template>

<script>
export default {
    name: "Manage_room_add",
    data() {
        return {
            list: [],
            day: '',
            TITLE: ''
        };
    },
    computed: {
        getId() {
            return this.$store.getters.getId
        }
    },
    methods: {
        goBack: function() {
            this.$router.push("/manage_room")
        },
        submitLog: function() { // 등록 버튼
            var Possible_ = registerForm.possible.value;
            var Title_ = registerForm.TITLE.value;
            console.log('Possible_= ' + Possible_);
            console.log('Title_= ' + Title_);
            
            if (Title_ == "") { alert("회의실 이름을 입력해주세요"); return; }
            if (Possible_ == "") { alert("주말 예약 가능 여부를 입력해주세요"); return; }

            var url = 'http://localhost:8888' + `/add/room?title=${Title_}&possible=${Possible_}`;
            console.log(url)
            this.$http.get(url)
                .then((result) => {
                    consolea.log(result)
                    if (result.data.status == 'success') { // 등록
                        console.log('success')
                        alert("성공적으로 등록했습니다!");
                        this.$router.push("/Manage_room")
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
