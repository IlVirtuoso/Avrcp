<template>
<div v-bind:id="id" class="StackedChartContainer">


</div>
</template>

<script lang="ts">
import { defineComponent, VueElement } from "vue";
import * as d3 from "d3";
import * as plotly from "plotly.js-dist-min"
import DataManager from "../Support/DataManager";
import { fileURLToPath } from "url";

export default defineComponent({
    props:['id', 'dataIn','parameters', 'country', 'startYear', 'endYear'],

    data(){return{datamanager: new DataManager()}},

    updated(){
        this.datamanager = this.dataIn;
        this.Draw();
    },

    methods:{

        CreateTraces(): plotly.Data[]{
            var data : Array<Partial<plotly.Data>> = new Array<Partial<plotly.Data>>()
            var params :Array<{label:string, value:string, color:plotly.Color, stackgroup:string}> = this.parameters;
            params.forEach((param) =>{
                var years: Array<number> = new Array<number>();
                var values: Array<number> = new Array<number>();
                this.datamanager.GetIso(this.country).map((row)=>{
                    var exyear = parseInt(row["year"] as unknown as string);
                    if(exyear >= this.startYear &&  exyear <= this.endYear){
                    years.push(exyear);
                    values.push(parseFloat(row[param.value] as any as string));
                    }
                });
                data.push({
                    x:years,
                    y:values,
                    stackgroup:param.stackgroup,
                    name:param.label,
                    marker:{
                        color:param.color
                    },
                })
            });

            return data;
        },

        Draw(){
            plotly.newPlot(this.id,this.CreateTraces(),{title: this.datamanager.IsoToCountryName(this.country)});
            console.log(this.CreateTraces());
        }
    },

    watch:{
        parameters(oldval,newval){
            this.Draw();
        }
    }
});

</script>