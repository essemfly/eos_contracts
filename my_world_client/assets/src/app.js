import Vue from 'vue';
import Eosjs from 'eosjs';
import App from './App.vue';
import Antd from 'ant-design-vue';
import 'ant-design-vue/dist/antd.css';

Vue.use(Antd);

new Vue({
  el: '#app',
  data: function () {
    const chain = {
      main: 'aca376f206b8fc25a6ed44dbdc66547c36c6c33e3a119ffbeaef943642f0e906', // main network
      jungle: '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca', // jungle testnet
      sys: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f' // local developer
    };

    const config = {
      chainId: chain.sys,
      keyProvider: [
        '5HuD228A2ZUDZvxMJadS7QLFBpLvX1m2NHigbM76VQs74t68LX1',
        '5Jbstf6aWQpf3cm9nXTCW2YjjGG8uyMQLFwSohE3sTUGGDk5Emu',
        '5JvzWhixac5q7SNZLm4DEmuXFwN5tqEAVGirWDHjWBnqh77Qnz9',
        '5KGPjXLmpmsdSSpkosx3rC42Uh9LzdabVoHSF1cwPCAkQL1DFYk',
        '5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3',
        '5JFFuyMhV1nCj4T5UWh3uF59un9372EQruBLqrHjHRkcz5bmHNa',
        '5Jmsawgsp1tQ3GD6JyGCwy1dcvqKZgX6ugMVMdjirx85iv5VyPR',
        '5Jbstf6aWQpf3cm9nXTCW2YjjGG8uyMQLFwSohE3sTUGGDk5Emu'
      ],
      httpEndpoint: "http://localhost:8888",
      expireInSeconds: 60,
      broadcast: true,
      verbose: false,
      sign: true
    };

    return {
      eos: Eosjs(config),
      options: {
        authorization: ["seokmin@active"],
        broadcast: true,
        sign: true
      }
    };
  },
  render: function (h) {
    const path = window.location.pathname;
    switch (path) {
      case "/":
        return h(App);
      // case "/main":
      //   return h(Main);
    }
  }
})