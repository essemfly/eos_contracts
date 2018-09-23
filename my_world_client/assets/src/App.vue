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
            <a-avatar slot="avatar" :src=item.avatar_url />
            <a slot="title">{{item.title}}</a>
          </a-list-item-meta>
          <div>{{item.content}}</div>
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

  // REFACTORING NEEDED
    let goodnews_feeds = await this.$parent.eos.getActions("goodnews");
    let badnews_feeds = await this.$parent.eos.getActions("badnews");
    let weather_feeds = await this.$parent.eos.getActions("weather");
    let babies_feeds = await this.$parent.eos.getActions("babies");
    
    for (let i=0; i<goodnews_feeds.actions.length; i++) {
      this.feeds.push(
        {
          "account": goodnews_feeds.actions[i].action_trace.act.account,
          "author": goodnews_feeds.actions[i].action_trace.act.data.author,
          "title": goodnews_feeds.actions[i].action_trace.act.data.title,
          "content": goodnews_feeds.actions[i].action_trace.act.data.content.substring(0, 40),
          "avatar_url": "http://www.thetulsavoice.com/images/cache/cache_8/cache_3/cache_1/badnews-b4e8b138.jpeg?ver=1507762210&aspectratio=1",
        }
      )
    }

    for (let i=0; i<badnews_feeds.actions.length; i++) {
      this.feeds.push(
        {
          "account": badnews_feeds.actions[i].action_trace.act.account,
          "author": badnews_feeds.actions[i].action_trace.act.data.author,
          "title": badnews_feeds.actions[i].action_trace.act.data.title,
          "content": badnews_feeds.actions[i].action_trace.act.data.content.substring(0, 40),
          "avatar_url": "https://media.istockphoto.com/photos/good-news-picture-id515275018?k=6&m=515275018&s=612x612&w=0&h=3cntkSAPZuzNdb_il1_txsrf7O2zbSk_THbS2jS_3Rs="
        }
      )
    }

    for (let i=0; i<weather_feeds.actions.length; i++) {
      this.feeds.push(
        {
          "account": weather_feeds.actions[i].action_trace.act.account,
          "author": weather_feeds.actions[i].action_trace.act.data.author,
          "title": "Weather",
          "content": weather_feeds.actions[i].action_trace.act.data.regions[0] + ": " + weather_feeds.actions[i].action_trace.act.data.weather[0] + " " + weather_feeds.actions[i].action_trace.act.data.temperatures[0],
          "avatar_url": "https://lh3.googleusercontent.com/Rd7qq4MBthBBunInLWDt7Tpm_zIX6FqVM-4gZmhxHnNo6vQqYRo5c4v6riu0_EgdR2Lf"
        }
      )
    }

    for (let i=0; i<babies_feeds.actions.length; i++) {
      this.feeds.push(
        {
          "account": babies_feeds.actions[i].action_trace.act.account,
          "author": babies_feeds.actions[i].action_trace.act.data.author,
          "title": "Amount of drinking milks",
          "content": babies_feeds.actions[i].action_trace.act.data.child_name + ": " + babies_feeds.actions[i].action_trace.act.data.meal_type + " " + babies_feeds.actions[i].action_trace.act.data.volume,
          "avatar_url": "https://i2-prod.mirror.co.uk/incoming/article6614278.ece/ALTERNATES/s615/Baby.jpg"
        }
      )
    }
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