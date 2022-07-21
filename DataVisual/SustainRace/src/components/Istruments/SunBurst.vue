<template>
<div v-bind:id="id" class="SunBurstContainer">


</div>
</template>

<script lang="ts">
import { defineComponent, VueElement } from "vue";
import * as d3 from "d3";
import * as plotly from "plotly.js-dist-min"
import DataManager from "../Support/DataManager";
import { fileURLToPath } from "url";
import { DSVRowString } from "d3-dsv";


export default defineComponent({
    props:['id', 'dataIn', 'parentsDict', 'year', 'iso_code', "startYear","endYear"],

    data() {return {datamanger: new DataManager(), redraw:true}},
    updated(){
        this.datamanger = this.dataIn;
        if(this.redraw){
            this.Draw();
            this.redraw = false;
        }
        else{
            this.Animate();
        }
    },

    methods:{
        BuildData(year:number): plotly.Data[]{
            var dict : Array<{id:string,label: string, parent: string,color: plotly.Color}> = this.parentsDict;
            var values =  new Array<number>();

            this.datamanger.GetYear(year).map((row: DSVRowString) =>{
                if(row["iso_code"] == this.iso_code){
                dict.forEach((param)=>{
                    values.push(parseFloat(parseFloat(row[param.id] as string).toFixed(3)));
                });
                }
            } 
            );
            
            for(var i = 0 ; i < 3; i++) values[i] += 0.01;

            var data : plotly.Data[] = [{
                type: "sunburst",
                labels: dict.map((elem)=> elem.label),
                ids: dict.map((elem)=> elem.id),
                parents: dict.map((elem)=> elem.parent),
                values:  values,
                marker:{
                    colors:dict.map((elem)=> elem.color),
                },
                branchvalues:"total"
            }];
            return data;      
        },


        BuildFrames(): Partial<plotly.Frame>[]{
            var frames : Array<Partial<plotly.Frame>> = new Array<Partial<plotly.Frame>>();
            for(var i = this.startYear; i <= this.endYear; i++){
                frames.push({
                    name: i,
                    data:this.BuildData(i)
                });
            }
            return frames;
        },

         Animate(): void{
             plotly.animate(
                this.id,
                {
                    data:this.BuildData(this.year),
                 transition: [{duration: 10, easing: 'linear'}],
                }
             );
        },

        Draw(): void{
            plotly.newPlot(this.id,this.BuildData(this.year));
        }
    },

    watch:{
        iso_code(oldval,newval){
            if(oldval != newval){
                
            }
        }
    }
});

</script>