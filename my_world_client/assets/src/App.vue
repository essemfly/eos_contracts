<template>
  <div id="landing" style="background:#ECECEC; padding:30px;">
    <a-card class="container" title="EOS Alert Messages" :bordered="false" style="width: 100%; height: 100%; overflow-y: scroll; margin-left: auto; margin-right: auto;">
      <p>Only permitted accounts post an alert</p>
      <a-list
        itemLayout="horizontal"
        :dataSource="alerts"
      >
        <a-list-item slot="renderItem" slot-scope="item, index">
          <a-list-item-meta
            :description="item.time"
          >
            <a slot="title">{{item.title}} - "{{item.author}}" reported</a>
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
      alerts: []
    };
  },
  async created() {
    let alerts = await this.$parent.eos.getTableRows(true, "alert", "alert", "alerts")
    
    for(let i=0; i<alerts.rows.length; i++) {
      alerts.rows[i].time = "updated:" + moment.unix(alerts.rows[i].updated_at).format("h:mm, MMDD") + " created: " + moment.unix(alerts.rows[i].created_at).format("h:mm, MMDD")  
    }
    this.alerts = alerts.rows;
  },
  methods: {
    
  }
};
</script>

<style lang="scss">
.record-list {
  margin-bottom: 10px;
}
</style>