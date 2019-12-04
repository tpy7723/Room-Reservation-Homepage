import Vue from 'vue'
import Router from 'vue-router'
import Hello from '@/components/Hello'
import Login from '@/components/Login'
import Join from '@/components/Join'
import Reservation from '@/components/Reservation'
import Reserv_add from '@/components/Reserv_add'
import Reserv_detail from '@/components/Reserv_detail'
import Manage_room from '@/components/Manage_room'
import Manage_room_add from '@/components/Manage_room_add'


Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'hello',
      component: Hello
    },
    {
      path: '/login',
      name: 'Login',
      component: Login
    },
    {
      path: '/join',
      name: 'join',
      component: Join
    },
    {
      path: '/reservation',
      name: 'reservation',
      component: Reservation
    },
    {
      path: '/reserv_add',
      name: 'reserv_add',
      component: Reserv_add
    },
    {
      path: '/reserv_detail',
      name: 'reserv_detail',
      component: Reserv_detail
    },
    {
      path: '/manage_room',
      name: 'manage_room',
      component: Manage_room
    },
    {
      path: '/manage_room_add',
      name: 'manage_room_add',
      component: Manage_room_add
    }
  ]
})
