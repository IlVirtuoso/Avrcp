<template>
<p>Loaded</p>
<button @click="AddParameter()">AddParameter</button>
<Map id="Map" v-bind:dataIn="data" parameter="gas_share_elec" title="gas" startYear=1990 endYear=2021 v-bind:currentYear="year" projectionType="natural earth" />
</template>


<script lang="ts">
import { defineComponent, render} from "vue"
import * as d3 from "d3"
import Map from "./Istruments/Map.vue"
import DataManager from "./Support/DataManager"
import { watch } from "fs";
import { loadavg } from "os";
import { Console } from "console";
import TemporalHistogram from "./Istruments/TemporalHistogram.vue";

export default defineComponent({
    data: () => { return { datamanager: new DataManager() , data: new Object(), year:1990 , parameters:["oil_share_elec", "gas_share_elec","coal_share_elec"]} },
    mounted() {
        this.datamanager.Load("/owid-energy-data-1990.csv").then(()=> this.Load());
    },
    methods: {
        Load: function () {
            console.log(this.datamanager.DataFrame());
            this.data = this.datamanager;

            
        },

        Advance(){
            this.year++;
        },

        AddParameter(){
            this.parameters.push("solar_share_elec");
        }
    },
    components: { Map, TemporalHistogram },
   
});


</script>