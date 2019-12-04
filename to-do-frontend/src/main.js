// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import App from './App'
import router from './router'
import axios from 'axios'
import moment from 'moment';
import 'moment-timezone';
import { store } from './store'
import BootstrapVue from 'bootstrap-vue'
import 'bootstrap/dist/css/bootstrap.min.css'
import 'bootstrap-vue/dist/bootstrap-vue.css'
import DateTimePicker from "simple-vue2-datetimepicker";

import { Datetime } from 'vue-datetime'
// You need a specific loader for CSS files
import 'vue-datetime/dist/vue-datetime.css'

Vue.use(Datetime)
Vue.use(DateTimePicker);
Vue.use(BootstrapVue)
Vue.component('datetimepicker', DateTimePicker);
Vue.component('datetime', Datetime);
Vue.config.productionTip = false

Vue.prototype.$http = axios
Vue.prototype.$moment = moment
/* eslint-disable no-new */
new Vue({
  el: '#app',
  router,
  store,
  template: '<App/>',
  components: { App }
})
