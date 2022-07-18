<template>
<div>
    <p>Map Loaded</p>
<div class="MapContainer" v-bind:id="id" >
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


        DrawLayout(year:number) : Partial<plotly.Layout> {
            var layout = {
                title: this.title,
                geo:{
                    projection:{
                        type: this.projectionType,
                        location: this.datamanger.GetYear(year).map((row: {[key:string]:any}) => row["country"]),
                    }
                }

            };
            return layout;
        },

        BuildLocableData(year: number): plotly.Data[]{

           var data : Partial<plotly.Data[]> = [{
                type:  "choropleth",
                locationmode: "country names",
                locations : this.datamanger.GetYear(year).map((row:{[key:string]:any})=> row["country"]),
                z: this.datamanger.GetYear(year).map((row:{[key:string]:any})=> row[this.parameter]),
                zmax:100,
             }];
             return data as plotly.Data[];
        },

        Animate(): void{
             plotly.animate(
                this.id,
                [this.currentYear -1, this.currentYear],
                {
            frame: [
                   {duration: 200},
                   {duration: 200},
                 ],
                 transition: [
                   {duration: 100, easing: 'elastic-in'},
                   {duration: 100, easing: 'cubic-in'},
                 ],
                 mode:'afterall'
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
            })
        }
    }
});


</script>

<style>

</style>