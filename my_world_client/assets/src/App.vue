<template>
  <div id="landing" style="background:#ECECEC; padding:30px;">
    <a-card class="container" title="EOS Contracts to Follow" :bordered="false" style="width: 100%; height: 100%; overflow-y: scroll; margin-left: auto; margin-right: auto; margin-bottom: 40px;">
     <a-row :gutter="16">
        <a-col :span="6">
          <p>card content</p>
        </a-col>
        <a-col :span="6">
          <p>card content</p>
        </a-col>
      </a-row>
    </a-card>
    <a-card class="container" title="EOS Contracts to Follow" :bordered="false" style="width: 100%; height: 100%; overflow-y: scroll; margin-left: auto; margin-right: auto;">
      <p>Recommended contracts</p>
      <a-row class="record-list">
        <a-col :span="12">
          <a-radio-group :value="milk_type" @change="handleTypeChange">
            <a-radio-button value="powdered">분유</a-radio-button>
            <a-radio-button value="breast">모유</a-radio-button>
          </a-radio-group>
        </a-col>
      </a-row>
      <a-row class="record-list">
        <a-col :span="10">
          <a-time-picker format="HH:mm" :minuteStep="15"  @change="handleTimeChange" :value="milk_time" />
        </a-col>
        <a-col :span="12" :offset="2">
          <a-radio-group :value="milk_day" @change="handleDayChange" style="float:right;">
            <a-radio-button value="today">오늘</a-radio-button>
            <a-radio-button value="yesterday">어제</a-radio-button>
          </a-radio-group>
        </a-col>
      </a-row>
      
      <a-row class="record-list">
        <a-col :span="16">
          <a-slider :min="50" :max="240" :step="10" v-model="milk_volume" @afterChange="handleVolumeChange" />
        </a-col>
        <a-col :span="8">
          <a-input-number
            :min="50"
            :max="240"
            :step="10"
            style="float: right;"
            v-model="milk_volume"
            :formatter="value => `${value} ml`"
          />
        </a-col>
      </a-row>
      <a-button type="primary" v-on:click="record_milk">저장</a-button>
      <a-divider> Histories </a-divider>
      <a-list
        itemLayout="horizontal"
        :dataSource="histories"
      >
        <a-list-item slot="renderItem" slot-scope="item, index">
          <a-list-item-meta
            :description="item.ate_at"
          >
            <a slot="title">{{item.meal_type == "breast" ? "모유" : "분유"}}</a>
          </a-list-item-meta>
          {{item.volume}} ml
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
      histories: [],
      child_name: "이정빈",
      milk_type: "powdered",
      milk_volume: 120,
      milk_day: "today",
      milk_time: moment(),
    };
  },
  async created() {
    let action_records = await this.$parent.eos.getActions("user")
    console.log(action_records);
    this.histories = action_records.actions.map(
      action => action.action_trace.act.data
    );
    console.log(this.histories);
  },
  methods: {
    moment,
    handleTimeChange(e) {
      this.milk_time = e;
    },
    handleDayChange(e) {
      this.milk_day = e.target.value;
    },
    handleTypeChange(e) {
      this.milk_type = e.target.value;
    },
    handleVolumeChange(value) {
      this.milk_volume = value;
    },
    record_milk: async function() {
      let milk_type = this.milk_type == "breast" ? "모유":"분유";
      let report_date = this.milk_day == "today" ? moment().format("YYYYMMDD") : moment().subtract(1, 'days').format("YYYYMMDD");
      let milk_ate_time = report_date + " " + this.milk_time.format("h:mma");

      console.log(milk_ate_time)
      console.log(milk_ate_time.unix)
      let tx_write = await this.$parent.eos.transaction("daybit", daybit => {
        daybit.write(
          "daybit",
          milk_type,
          this.child_name,
          this.milk_volume,
          milk_ate_time,
          this.$parent.options
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
</style>