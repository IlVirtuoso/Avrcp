<template>
   <el-slider  v-model="mapselectedyear" :step="1" :min="1990" :max="2020" show-stops/>
<el-container>
    <el-aside width="50%">
    <SunBurstManager v-bind:currentYear="mapselectedyear" v-bind:dataIn="data" v-bind:iso_code="countryTarget" />
</el-aside>
<el-main>
<MapManager v-bind:year="mapselectedyear" v-model:year="mapselectedyear" v-bind:dataIn="data" @location_clicked="DisplayDataLocation($event)" />
</el-main>

</el-container>
<el-container>
    <el-main>
    <TemporalChartManager v-bind:dataIn="data" v-bind:country="countryTarget" />
    </el-main>
</el-container>
</template>


<script lang="ts">
import { defineComponent, render} from "vue"
import * as d3 from "d3"
import Map from "./Istruments/Map.vue"
import DataManager from "./Support/DataManager"
import { watch } from "fs";
import { loadavg } from "os";
import { Console } from "console";
import MapManager from "./Managers/MapManager.vue";
import TemporalChartManager from "./Managers/TemporalChartManager.vue";
import SunBurstManager from "./Managers/SunBurstManager.vue";
import BubbleChartManager from "./Managers/BubbleChartManager.vue";
export default defineComponent({
    data: () => { return { datamanager: new DataManager() , data: Object() , countryTarget:"CHN"
    , mapselectedyear: 2010}},
    mounted() {
        this.datamanager.Load("/owid-energy-data-1990-noaggregate.csv").then(()=> this.Load());
    },
    methods: {
        Load: function () {
            this.data = this.datamanager;
        },

        DisplayDataLocation(iso_code:string){
            console.log(iso_code);
            this.countryTarget = iso_code;
        }
    },
    components: { MapManager, TemporalChartManager, SunBurstManager, BubbleChartManager },


});


</script>