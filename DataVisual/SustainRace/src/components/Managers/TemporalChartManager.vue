<template>
<el-header>
 <el-slider  v-model="viewrange" :step="1" :min="1990" :max="2020" show-stops range/>
 <el-select v-model="chart">
 <el-option label="Chart" value="Chart" />
 <el-option label="Histogram" value="Histogram"/>
 </el-select>
</el-header>
<el-main>
<StackedChart v-if="chart == 'Chart'" id="stackedchart" v-bind:parameters="parameters" v-bind:start-year="viewrange[0]" v-bind:end-year="viewrange[1]" v-bind:country="country" v-bind:dataIn="dataIn"  />
<TemporalHistogram v-if="chart == 'Histogram'"  id="histogram" v-bind:parameters="parameters" v-bind:start-year="viewrange[0]" v-bind:end-year="viewrange[1]" v-bind:country="country" v-bind:dataIn="dataIn" />
</el-main>
</template>


<script lang="ts">

import { defineComponent, VueElement } from "vue";
import * as d3 from "d3";
import * as plotly from "plotly.js-dist-min"
import DataManager from "../Support/DataManager";
import { fileURLToPath } from "url";
import TemporalHistogram from "../Istruments/TemporalHistogram.vue";
import StackedChart from "../Istruments/StackedChart.vue";
const parametersType :Array<{label:string,value:string,color:plotly.Color,stackgroup:string}> =[
    {label:'Fossil %', value:'fossil_share_elec', color: '#000000', stackgroup:'aggregate'},
    {label: 'Renewable %', value:'renewables_share_elec', color: '#008000', stackgroup:'aggregate'},
    {label: 'Other renewables %', value:'other_renewables_share_elec', color: '#0080FF', stackgroup:'aggregate'},
    {label: 'Nuclear %', value:'nuclear_share_elec', color: '#FF43F0', stackgroup:'aggregate'}
];

export default defineComponent({
    props: ["dataIn", "country"],
    data() { return { datamanager: new DataManager(), loaded: false, viewrange: [2010,2020],
     parameters: [parametersType[0], parametersType[1],parametersType[2],parametersType[3]],
     chart:"Chart",
     }},

    mounted() {
    },
    updated() {
    },
    methods: {},
    watch: {},
    components: { TemporalHistogram , StackedChart}
});


</script>

<style>

</style>