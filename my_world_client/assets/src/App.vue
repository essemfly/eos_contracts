<template>
  <div id="landing" style="background:#ECECEC; padding:30px;">
    <a-card class="container" title="EOS Alert Messages" :bordered="false" style="width: 100%; overflow-y: scroll; margin-left: auto; margin-right: auto;">
      <p>Only permitted accounts post an alert</p>
      <a-list
        itemLayout="horizontal"
        :dataSource="alerts"
      >
        <a-list-item slot="renderItem" slot-scope="item, index">
          <a-list-item-meta
            :description="item.time"
          >
            <a slot="title">{{item.title}}: {{item.description}}</a>
          </a-list-item-meta>
          <div>"{{item.author}}" reported</div>
        </a-list-item>
      </a-list>
    </a-card>
    <a-card class="container" title="Follow others" :bordered="false" style="width: 100%; overflow-y: scroll; margin-left: auto; margin-right: auto;">
      <p>Follow other contracts' changes and logs</p>
      <a-list
        :grid="{ gutter: 16, xs: 1, sm: 2, md: 4, lg: 4, xl: 6, xxl: 3 }"
        :dataSource="apps"
      >
        <a-list-item slot="renderItem" slot-scope="item, index" v-bind:class="{ active: item.is_follow }" v-on:click="follow_app(item.id)">          
          <a-list-item-meta 
            :description="item.description">
            <a-avatar slot="avatar" :src=item.avatar_url />
            <a slot="title">{{item.name}}</a>
          </a-list-item-meta>
        </a-list-item>
      </a-list>
    </a-card>

    <a-card class="container" title="Contracts Feed" :bordered="false" style="width: 100%; overflow-y: scroll; margin-left: auto; margin-right: auto;">
      <p>Follow other contracts' changes and logs</p>
      <a-list
        :dataSource="feeds"
      >
        <a-list-item slot="renderItem" slot-scope="item, index">          
          <a-list-item-meta>
            <a-avatar slot="avatar" src="https://zos.alipayobjects.com/rmsportal/ODTLcjxAfvqbxHnVXCYX.png" />
            <a slot="title">{{item.name}}</a>
          </a-list-item-meta>
          <div>{{item.description}}</div>
        </a-list-item>
      </a-list>
    </a-card>
  </div>
</template>

<script>
import moment from 'moment';

export default {
  name: "landing",
  data() {
    return {
      alerts: [],
      apps: [],
      my_apps: [],
      followers: [],
      feeds: [],
    };
  },
  async created() {
    let alerts = await this.$parent.eos.getTableRows(true, "alert", "alert", "alerts");
    
    for(let i=0; i<alerts.rows.length; i++) {
      alerts.rows[i].time = "updated:" + moment.unix(alerts.rows[i].updated_at).format("h:mm, MMDD") + " created: " + moment.unix(alerts.rows[i].created_at).format("h:mm, MMDD")  
    }
    this.alerts = alerts.rows;

    let my_apps = await this.$parent.eos.getTableRows(true, "myworld", "myworld", "flwrecords");
    this.my_app_ids = my_apps.rows.filter(contract => contract.author = "user").map(contract => contract.id);

    let apps = await this.$parent.eos.getTableRows(true, "myworld", "myworld", "apps");
    for(let i=0; i<apps.rows.length; i++) {
      apps.rows[i].time = "updated:" + moment.unix(apps.rows[i].updated_at).format("h:mm, MMDD") + " created: " + moment.unix(apps.rows[i].created_at).format("h:mm, MMDD");
      apps.rows[i].is_follow = apps.rows[i].id in this.my_apps ? true : false;
    }
    this.apps = apps.rows;

  // my app id를 써야 하는데 필요한건 그냥 contract!
    let goodnews_feeds = await this.$parent.eos.getActions("goodnews");
    let badnews_feeds = await this.$parent.eos.getActions("badnews");
    let weather_feeds = await this.$parent.eos.getActions("weather");
    let soccer_feeds = await this.$parent.eos.getActions("soccer");
    
    console.log(weather_feeds);
    this.feeds = goodnews_feeds.actions.map(
      action => action.action_trace.act
    );
    this.feeds.push(badnews_feeds.actions.map(
      action => action.action_trace.act
    ));
    this.feeds.push(weather_feeds.actions.map(
      action => action.action_trace.act
    ));
    this.feeds.push(soccer_feeds.actions.map(
      action => action.action_trace.act
    ));

    console.log(this.feeds)
  },
  methods: {
    moment,
    follow_app: async function(app_id) {
      await this.$parent.eos.transaction("myworld", myworld => {
        myworld.follow(
          "seokmin",
          app_id
        );
      });
    }
  }
};
</script>

<style lang="scss">
.record-list {
  margin-bottom: 10px;
}
.active {
  border-radius: 10px;
  padding: 10px;
  margin-right: 10px;
  border: 5px solid yellowgreen;
}
</style>