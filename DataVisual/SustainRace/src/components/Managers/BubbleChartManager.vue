<template>
<el-container>
    <BubbleChart id="bubblechart" v-bind:dataIn="dataIn" v-bind:year="year" v-bind:xtrace="xtrace"
    v-bind:ytrace="ytrace" v-bind:sizetrace="sizetrace" v-bind:colorscale="colorscale"/>
</el-container>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import * as d3 from "d3";
import * as plotly from "plotly.js-dist-min"
import DataManager from "../Support/DataManager";
import { fileURLToPath } from "url";
import { watch } from "fs";
import BubbleChart from "../Istruments/BubbleChart.vue";
enum Mode{
    GDPCAPITAEMISSION,

};

export default defineComponent({
    props:['dataIn', 'year'],
    data(){ return{ xtrace: new Array<Number>(), ytrace: new Array<Number>(), sizetrace: new Array<Number>(), colorscale: "", datamanager: new DataManager(), mode:Mode.GDPCAPITAEMISSION}},
    updated(){
        this.datamanager = this.dataIn;
        this.FillDecisor();
    },

    methods:{

        FillDecisor():void{
            switch(this.mode){
                case Mode.GDPCAPITAEMISSION:
                    this.EmissionGDPPerCapita();
                    break;
            }
        },

        EmissionGDPPerCapita(){
            this.xtrace = this.datamanager.GetYear(this.year).map((row )=> parseInt(row["gdp"] as string)/parseInt(row["population"] as string));
            this.ytrace= this.datamanager.GetYear(this.year).map((row)=> parseInt(row["greenhouse_gas_emissions"] as string));
            this.sizetrace =this.datamanager.GetYear(this.year).map((row)=> parseInt(row["population"] as string)
            /50000000);

        }

    },

    components:{BubbleChart}


});
</script>