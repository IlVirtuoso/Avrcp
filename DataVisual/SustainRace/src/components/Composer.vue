<template>
<p>Loaded</p>
<Map id="Map" v-bind:dataIn="data" parameter="Coal (% electricity)" />
</template>


<script lang="ts">
import { defineComponent} from "vue"
import * as d3 from "d3"
import Map from "./Map.vue"
import DataManager from "./Support/DataManager"

var datamanager = new DataManager();



export default defineComponent({
    data: () => { return { data: Object }; },
    mounted() {
        this.data = d3.csv("/share-elec-produc-by-source.csv") as any;
        console.log(this.data);
        console.log(datamanager.a);
    },
    methods: {
        Load: function () {
            return this.data;
        }
    },
    components: { Map }
});


</script>