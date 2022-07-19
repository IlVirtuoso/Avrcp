<template>
<p>Loaded</p>
<MapManager v-bind:dataIn="data" />
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
import MapManager from "./Managers/MapManager.vue";

export default defineComponent({
    data: () => { return { datamanager: new DataManager() , data: Object()  }},
    mounted() {
        this.datamanager.Load("/owid-energy-data-1990-noaggregate.csv").then(()=> this.Load());
    },
    methods: {
        Load: function () {
            this.data = this.datamanager;
        }
    },
    components: { Map, TemporalHistogram, MapManager },


});


</script>