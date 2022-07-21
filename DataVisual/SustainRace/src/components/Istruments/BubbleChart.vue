<template>
<div class="BubbleChartContainer" v-bind:id="id">

</div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import * as d3 from "d3";
import * as plotly from "plotly.js-dist-min"
import DataManager from "../Support/DataManager";
import { fileURLToPath } from "url";
import { DSVRowString } from "d3-dsv";

export default defineComponent({


    props:['id','dataIn', 'xtrace', 'ytrace', 'sizetrace', 'year', 'colorscale' ],
    data(){return{ datamanager : new DataManager()}},

    updated(){
        this.datamanager = this.dataIn;
        this.Draw();
    },

    methods:{

        BuildData(): Partial<plotly.Data>[]{

            var data : Partial<plotly.Data>[] = [{
                mode:"markers",
                text: this.datamanager.GetYear(this.year).map((row)=> row["country"]) as any,
                x: this.xtrace,
                y: this.ytrace,
                marker:{
                    size: this.sizetrace
                },
                colorscale:this.colorscale
            }]
            return data;

        },



        Draw(){
            plotly.newPlot(this.id,this.BuildData())
        }
    },



});

</script>