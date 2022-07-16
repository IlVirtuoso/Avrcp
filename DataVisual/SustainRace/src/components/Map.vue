<template>
<div>
<div class="MapContainer" id="Map" >
</div>
</div>
</template>


<script lang="js">

import { defineComponent } from "vue";
import * as d3 from "d3";
import Plotly from "plotly.js-dist-min"
import { style } from "d3";

export default defineComponent({

    props:['id', 'parameter', 'dataIn', 'title', 'projectionType'],
    data:()=>{
        return { dataframe: Promise, Id : "" }
    },

    mounted(){
        
    },

    updated(){
        this.Id = this.id;
        this.dataIn.then((result)=>{
            this.dataframe = result;
            this.Load();
        });
    },

    methods:{
        
        Load: function(result){

            console.log(this.dataframe);
            this.Draw();
        },

        Unpack: function(rows ,key ){
            var elements = [];
            rows.forEach(row => {
                elements.push(row[key]);
            });
            return elements;
        },

        DrawLayout: function() {
            var layout = {
                title: this.title,
                geo:{
                    projection:{
                        type: this.projectionType,
                        location: this.Unpack(this.dataframe,"Entity"),
                    }
                },
                style: "dark",

            };
            return layout;
        },

        BuildLocableData: function() {

           

             var data = [{
                type: 'choropleth',
                locationmode: "country names",
                locations : this.Unpack(this.dataframe,"Entity"),
                z: this.Unpack(this.dataframe,this.parameter),
                zmax:100,
                
             }];
             return data;
        },

        Draw : function (){
            Plotly.newPlot(this.id,this.BuildLocableData(),this.DrawLayout())
        },






    }



    

})


</script>

<style>

</style>