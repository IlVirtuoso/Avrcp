<template>
<el-container>
    <el-header >
 

        <el-select class="m-2" v-model="parameter" placeholder="Data"  default-first-option>
        <el-option v-for="option in parameters"   :key="option.value" :label="option.label" :value="option"   />
    </el-select >
    <el-select class="m-2" v-model="projection" placeholder="Projection"  default-first-option >
        <el-option v-for="option in projections"  :key="option.value" :label="option.label" :value="option.value"   />
    </el-select >
    </el-header>


    <el-main>
    <Map id="Map" @location_clicked="($event) => $emit('location_clicked',$event)" v-bind:dataIn="dataIn" v-bind:parameter="parameter" v-bind:title="parameter" startYear=1990 endYear=2020 v-bind:currentYear="year" v-bind:projectionType="projection" />
    </el-main>

</el-container>
</template>


<script lang="ts">

import { defineComponent } from "vue";
import * as d3 from "d3";
import * as plotly from "plotly.js-dist-min"
import DataManager from "../Support/DataManager";
import { fileURLToPath } from "url";
import { watch } from "fs";
import Map from "../Istruments/Map.vue";


const parametersTypes = [
    {label: 'GDP', value: 'gdp', color:"Viridis", unit:"$" },
    {label: 'Greenhouse Gas Emissions' , value: 'greenhouse_gas_emissions', color:"Portland", unit:"CO2/Mton"},
    {label: 'Population', value: 'population', color: 'Bluered', unit:""},
    {label: 'Electricity Generated' , value: 'electricity_generation', color:"Jet", unit:"Twh"},
    {label: 'Electricity Demand' , value: 'electricity_demand', color:"Jet", unit:"Twh"},
    {label: 'Renewable Energy Per Capita', value: 'renewables_energy_per_capita', color: "", unit:"KWh*Person" },
] ;

const projectionTypes = [
    {label: 'Natural Earth', value: 'natural earth'},
    {label: 'Mercator' , value: 'mercator'},
    {label: 'Orthographic', value: 'orthographic'}
];

export default defineComponent({
    props: ["dataIn", "year"],
    data() { return { parameter: parametersTypes[0], projection: "natural earth", parameters: parametersTypes, projections:projectionTypes }; },
    methods: {
        updateYear(event: any) {

        },
    },
    watch: {
     
    },
    components: { Map },
    emits:['location_clicked']
});


</script>

<style>

</style>