<template>
<div>
<div class="TemporalHistogramContainer" v-bind:id="id" >
</div>
</div>
</template>


<script lang="ts">

import { defineComponent } from "vue";
import * as d3 from "d3";
import * as plotly from "plotly.js-dist-min"
import DataManager from "../Support/DataManager";
import { fileURLToPath } from "url";


export default defineComponent({
    props:['id', 'parameters', 'dataIn', 'startYear', 'endYear', 'country'],
    data(){return{ datamanager: new DataManager() , loaded: false }},

    mounted(){

    },

    updated(){
        this.datamanager = this.dataIn;
        if(!this.loaded){
        this.Draw();
        this.loaded = true;
        }
        else{
            this.Animate();
        }
    },

    methods:{


        CreateTraces(): plotly.Data[]{
            var data : Array<Partial<plotly.Data>> = new Array<Partial<plotly.Data>>()
            var params :Array<string> = this.parameters;
            params.forEach((param) =>{
                var years: Array<number> = new Array<number>();
                var values: Array<number> = new Array<number>();
                this.datamanager.GetCountry(this.country).map((row)=>{
                    years.push(parseInt(row["year"] as unknown as string));
                    values.push(parseFloat(row[param] as any as string));
                });
                data.push({
                    x:years,
                    y:values,
                    type:"histogram",
                    histfunc:"sum",
                    name:param,
                    autobinx:false,
                     xbins: {
                      end: parseInt(this.endYear), 
                      size: 0.5, 
                      start: parseInt(this.startYear),
                    }
                })
            });

            return data;
        },

        CreateLayout() : Partial<plotly.Layout>{
            return {
                barmode:"stack",

                xaxis:{title:"year"},
                yaxis:{title:"% of share", range:[0,100]}
            };
        },

        Animate(){
            console.log("launched animation");
             plotly.animate(this.id, {
                  data: this.CreateTraces() ,
                  layout: this.CreateLayout()
                }, {
                  transition: {
                    duration: 200,
                    easing: 'cubic-in-out'
                  },
                  frame: {
                    duration: 200
                  }
                });
        },

        Draw(){
            plotly.newPlot(this.id, this.CreateTraces(), this.CreateLayout());
        },

    },

    watch:{
        parameters:{
            immediate:false,
            deep:true,
            handler(){
                if(this.datamanager.DataFrame() != null){
                    this.Draw();
                }
            }
        }
    }
});


</script>

<style>

</style>