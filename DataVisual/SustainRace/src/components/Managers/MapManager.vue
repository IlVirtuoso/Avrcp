<template>
<el-container>
    <el-header>
    <el-slider v-model="year" :step="1" :min="1990" :max="2020"/>
    </el-header>
    <el-main>
    <Map id="Map" v-bind:dataIn="dataIn" v-bind:parameter="parameter" v-bind:title="parameter" startYear=1990 endYear=2020 v-bind:currentYear="year" projectionType="natural earth" />
    </el-main>
    <el-aside>
        <el-select v-model="parameter" v-bind:placeholder="parameters[0].label">
            <el-option v-for="option in parameters"  :key="option.value" :label="option.label" :value="option.value"   />
        </el-select >
    </el-aside>
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
    {label: 'GDP', value: 'gdp' },
    {label: 'Population', value: 'population'},
    {label: 'Greenhouse Gas Emissions' , value: 'greenhouse_gas_emissions'}
] ;

const projectionTypes = [
    {}
];

export default defineComponent({
    props: ["dataIn"],
    data() { return { parameter: "", projectionType: "", year: 1990, parameters: parametersTypes, projection:projectionTypes }; },
    methods: {
        updateYear(event: any) {

        }
    },
    watch: {},
    components: { Map }
});


</script>

<style>

</style>