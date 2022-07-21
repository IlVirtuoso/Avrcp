<template>
<div>
<div  class="MapContainer" v-bind:id="id" >
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

    props:['id', 'parameter', 'dataIn', 'title', 'projectionType', 'currentYear' , 'startYear', 'endYear'],
    data:()=>{
        return { datamanger: new DataManager(), Id : "", loaded:false }
    },

    mounted(){
        
    },

    updated(){
        this.Id = this.id;
        this.datamanger = this.dataIn;
        this.Load();
    },

    methods:{
        
        Load(): void{
            if(!this.loaded){
                this.Draw();
                this.loaded = true;
            }
            else{
                this.Animate();
            }
        },

        Show(data : any){
            console.log(data.points[0].location);
        },

        DrawLayout(year:number) : Partial<plotly.Layout> {
            var layout = {
                title: this.parameter.label + " " + this.parameter.unit,
                geo:{
                    projection:{
                        type: this.projectionType,
                        
                    },
                    mapbox:{
                        style:"dark"
                    }
                }

            };
            return layout;
        },

        BuildLocableData(year: number): plotly.Data[]{
           var data : Partial<plotly.Data[]> = [{
                type:  "choropleth",
                locationmode: "ISO-3",
                locations : this.datamanger.GetYear(year).map((row:{[key:string]:any})=> row["iso_code"]),
                z: this.datamanger.GetYear(year).map((row:{[key:string]:any})=> row[this.parameter.value]),
                colorbar:{
                    title:this.parameter.unit,
                },
                colorscale:this.parameter.color,
               // zmax: d3.max(this.datamanger.GetYear(year).map((row:{[key:string]:any})=> row[this.parameter.value]))
             }]; 
             return data as plotly.Data[];
        },

        Animate(): void{
             plotly.animate(
                this.id,
                [this.currentYear],
                {
            frame: [
                   {duration: 0},
                 ],
                 transition: [
                   {duration: 100, easing: 'elastic-in'},
                 ],
                }
             );
        },

        GenerateFrames():Partial<plotly.Frame>[]{
            var frames : Array<Partial<plotly.Frame>> = new Array<Partial<plotly.Frame>>();
            for(var i = this.startYear; i <= this.endYear; i++){
                frames.push({
                    name: i,
                    data:this.BuildLocableData(i)
                });
            }

            return frames;
        },

        Draw() : void{
            plotly.newPlot(this.id,this.BuildLocableData(this.currentYear) , this.DrawLayout(this.currentYear)).then(()=>{
                plotly.addFrames(this.id,this.GenerateFrames());
                
            });

            var plot = document.getElementById(this.id);
            (plot as any)?.on('plotly_click',(data : any)=> 
            this.$emit('location_clicked', data.points[0].location));
            
        }
    },
    emits:['location_clicked'],
    watch:{
        parameter(oldval,newval){
            if(oldval != newval) this.Draw();
        },
        projectionType(oldval,newval){
            if(oldval != newval) this.Draw();
        }
    }


});


</script>

<style>

</style>