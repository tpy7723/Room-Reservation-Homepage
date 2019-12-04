var express = require('express')
var app = express()
var bodyParser = require('body-parser')
const cors = require('cors');
app.use(bodyParser.urlencoded({ extended: true }))

//mysql 모듈 불러오기
var mysql = require('mysql')
app.use(cors());

//mysql 커넥션 생성
var connection = mysql.createConnection({
  host: "localhost", //서버 로컬 IP
  port: 3306,
  user: "root", //계정 아이디
  password: "1234", //계정 비밀번호
  database: "TEST2" //접속할 DB
})


//mysql 접속
connection.connect()

app.get('/', function (req, res) {
  res.send("Hello, World!")
  console.log('root입니다.')
})

// user 라우터
app.get('/join', function (req, res) {
  console.log('in /join');
  console.log(req.query);
  var ID = req.query.id;
  var PASSWORD = req.query.pw;
  var EMAIL = req.query.email;
  var NAME = req.query.name;

  const sha = require('sha256')

  PASSWORD = sha(PASSWORD)
  console.log(PASSWORD)

  connection.query('insert into 고객 values (?,?,?,?,default)', [ID, NAME, PASSWORD, EMAIL], (e, r, f) => {
    console.log(connection.query);
    res.setHeader('Content-Type', 'text/plain');
    if (e) {
      console.log(e)
      res.send({
        status: 'error',
        errMsg: '에러',
      })
    } else {
      res.send({
        status: 'success'
      })
      console.log('success');
    }
  })
});

app.get('/login', function (req, res) {
  res.setHeader('Content-Type', 'text/plain');
  console.log('in login')
  console.log(req.query);
  var id = req.query.id;
  var password = req.query.password;
  console.log('ID ' + id + '  password ' + password);

  const sha = require('sha256')

  password = sha(password) // 암호화

  connection.query('SELECT * from 고객 WHERE ID=?', [id], (e, r, f) => {
    if (r[0]) {
      if (e) {
        console.log('error : \n' + e)
        res.send({
          status: 'error',
          errMsg: '에러'
        })
      } else {
        console.log(r[0].비밀번호)
        if (r[0].비밀번호 == password) {
          console.log('login pass')
          res.send({
            status: 'success',
            result: JSON.parse(JSON.stringify(r)),
            field: f
          })
        } else {
          console.log('incorrect')
          res.send({
            status: "incorrect"
          })
        }
      }
    } else {
      console.log('no-user')
      res.send({
        status: "no-user"
      })
    }
  })
});

app.get('/call/reservation', function (req, res) {
  console.log('in call/reservation')
  console.log(req.query);
  var id_reserv = req.query.ID
  console.log(id_reserv)

  connection.query('SELECT * FROM 예약', (e, r, f) => {
    console.log('hihi')
    if (e) {
      console.log('에러' + e)
      res.send({
        status: 'error',
        errMsg: '에러'
      })
    } else {
      if (r[0]) {
        res.send({
          status: 'success',
          result: JSON.parse(JSON.stringify(r)),
        })

      } else {
        res.send({
          status: 'noexist',
          errMsg: '에러'
        })
      }
    }
  })
});

app.get('/delete/reservation', function (req, res) {
  console.log('in /delete/reservation')
  console.log(req.query);
  var id = req.query.ID;
  connection.query('delete from 예약 where 예약번호 = ?', [id], (e, r, f) => {
    console.log(connection.query);
    res.setHeader('Content-Type', 'text/plain');
    if (e) {
      console.log(e)
      res.send({
        status: 'error'
      })
    } else {
      res.send({
        status: 'success'
      })
    }
  })
});

app.get('/request/reservation', function (req, res) {
  console.log('in /request/reservation')
  console.log(req.query);
  var title_ = req.query.title;
  var start_ = req.query.start;
  var id_ = req.query.id;
  var end_ = req.query.end;
  var room_ = req.query.room;

  connection.query('insert into 예약 values (NULL,?,?,?,?,default,?)', [start_, end_, id_, title_, room_], (e, r, f) => {
    console.log(connection.query);
    res.setHeader('Content-Type', 'text/plain');
    if (e) {
      console.log(e)
      res.send({
        status: 'error',
        errMsg: '에러',
      })
    } else {
      res.send({
        status: 'success'
      })
      console.log('success');
    }
  })
});

app.get('/call/reserv_em', function (req, res) {
  console.log('in call/reserv_em')
  console.log(req.query);
  var id = req.query.id;
  connection.query('UPDATE 예약 SET 예약승인=? where 예약번호 = ?', ['1', id], (e, r, f) => {
    res.setHeader('Content-Type', 'text/plain');
    if (e) {
      console.log(e)
      res.send({
        status: 'error',
        errMsg: '에러',
      })
    } else {
      res.send({
        status: 'success',
        result: JSON.parse(JSON.stringify(r)),
        fields: f
      })
    }
  })
});

app.get('/call/room', function (req, res) {
  console.log('in call/room')
  var id_reserv = req.query.ID
  console.log(id_reserv)

  connection.query('SELECT * FROM 회의실', (e, r, f) => {
    if (e) {
      console.log('에러' + e)
      res.send({
        status: 'error',
        errMsg: '에러'
      })
    }
    else {
      if (r[0]) {
        res.send({
          status: 'success',
          result: JSON.parse(JSON.stringify(r)),
        })

      } else {
        res.send({
          status: 'noexist',
          errMsg: '에러'
        })
      }
    }
  })
});

app.get('/find', function (req, res) {
  console.log('in find')
  console.log(req.query)
  var ID = req.query.id

  connection.query('SELECT * FROM 고객 WHERE ID = ?', [ID], (e, r, f) => {
    console.log(connection.query)
    if (e) {
      console.log('에러' + e)
      res.send({
        status: 'error',
        errMsg: '에러'
      })
    } else {
      if (r[0]) {
        res.send({
          status: 'success',
          result: JSON.parse(JSON.stringify(r)),
        })
      } else {
        res.send({
          status: 'noexist',
          errMsg: '에러'
        })
      }
    }
  })
});

// user 라우터
app.get('/add/participant', function (req, res) {
  console.log('in /add/participant')
  console.log(req.query);
  var ID = req.query.id;

  connection.query('insert into 참석 select max(예약번호), ? from 예약;', [ID], (e, r, f) => {
    console.log(connection.query);
    res.setHeader('Content-Type', 'text/plain');
    if (e) {
      console.log(e)
      res.send({
        status: 'error',
        errMsg: '에러',
      })
    } else {
      res.send({
        status: 'success'
      })
      console.log('success');
    }
  })
});

app.get('/call/participant', function (req, res) {
  console.log('in call/participant')
  console.log(req.query);
  var id_reserv = req.query.ID

  connection.query('SELECT ID FROM 참석 WHERE 예약번호 = ?', [id_reserv], (e, r, f) => {
    if (e) {
      console.log('에러' + e)
      res.send({
        status: 'error',
        errMsg: '에러'
      })
    } else {
      if (r[0]) {
        res.send({
          status: 'success',
          result: JSON.parse(JSON.stringify(r)),
        })
      } else {
        res.send({
          status: 'noexist',
          errMsg: '에러'
        })
      }
    }
  })
});

app.get('/change/authority', function (req, res) {
  console.log('in /change/authority')
  console.log(req.query);
  var id = req.query.id;
  connection.query('UPDATE 회의실 SET 주말예약= (!주말예약) where 회의실이름 = ?', [id], (e, r, f) => {
    res.setHeader('Content-Type', 'text/plain');
    if (e) {
      console.log(e)
      res.send({
        status: 'error',
        errMsg: '에러',
      })
    } else {
      res.send({
        status: 'success',
        result: JSON.parse(JSON.stringify(r)),
        fields: f
      })
    }
  })
});

app.get('/delete/room', function (req, res) {
  console.log('in /delete/room')
  console.log(req.query);
  var id = req.query.ID;
  connection.query('delete from 회의실 where 회의실이름 = ?', [id], (e, r, f) => {
    console.log(connection.query);
    res.setHeader('Content-Type', 'text/plain');
    if (e) {
      console.log(e)
      res.send({
        status: 'error'
      })
    } else {
      res.send({
        status: 'success'
      })
    }
  })
});


app.get('/add/room', function (req, res) {
  console.log('in /add/room')
  console.log(req.query);
  var TITLE = req.query.title;
  var POSSIBLE = req.query.possible;

  connection.query('insert into 회의실 values(?,?);', [TITLE, POSSIBLE], (e, r, f) => {
    console.log(connection.query);
    res.setHeader('Content-Type', 'text/plain');
    if (e) {
      console.log(e)
      res.send({
        status: 'error',
        errMsg: '에러',
      })
    } else {
      res.send({
        status: 'success'
      })
      console.log('success');
    }
  })
});


//서버 시작
app.listen(8888, function () {
  console.log("server starting with 8888")
})