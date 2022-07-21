<template>
<el-header>
    <p>{{countryName}}</p>
</el-header>
<el-main>
    <SunBurst v-bind:dataIn="dataIn" id="sunburst" v-bind:year="currentYear" v-bind:iso_code="iso_code"
    v-bind:parentsDict="parentsDict" startYear="1990" endYear="2020" />
</el-main>
</template>


<script lang="ts">

import { defineComponent, VueElement } from "vue";
import * as d3 from "d3";
import * as plotly from "plotly.js-dist-min"
import DataManager from "../Support/DataManager";
import { fileURLToPath } from "url";
import SunBurst from "../Istruments/SunBurst.vue";

const values : Array<{label:string,id:string, parent:string, color:plotly.Color}> = [
    {label: "Fossil",id:"fossil_share_elec", parent:"",color:"#000000"},
    {label: "Nuclear",id:"nuclear_share_elec",parent:"",color:"#00FF00"},
    {label: "Renewables",id:"renewables_share_elec",parent:"",color:"#00FF00"},
    {label: "Hydro",id:"hydro_share_elec", parent:"renewables_share_elec",color:2},
    {label: "Wind",id:"wind_share_elec", parent:"renewables_share_elec",color:3},
    {label: "Solar",id:"solar_share_elec", parent:"renewables_share_elec",color:4},
    {label: "Biofuel",id:"biofuel_share_elec", parent:"renewables_share_elec",color:5},
    {label: "Coal",id:"coal_share_elec", parent:"fossil_share_elec",color:6},
    {label: "Oil",id:"oil_share_elec", parent:"fossil_share_elec",color:7},
    {label: "gas",id:"gas_share_elec", parent:"fossil_share_elec",color:7},
    

]

export default defineComponent({
    props: ["dataIn", "iso_code" , "currentYear"],
    data(){return {parentsDict: values, countryName: ""}},

    mounted() {
    },

    updated() {
        this.countryName = (this.dataIn as DataManager).IsoToCountryName(this.iso_code);
    },
    methods: {},
    watch: {},
    components: {  SunBurst }
});


</script>

<style>

</style>