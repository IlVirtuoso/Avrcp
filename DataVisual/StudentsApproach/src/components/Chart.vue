
<template>
<button @click="Click()">Press Me {{text}}</button>
<button @click="Remove()">Remove data</button>
<button @click="Draw()">Draw</button>
<div class="chart">
    <ul id="list">
        <li></li>
        <li></li>
    </ul>
</div>

<canvas id="chartContainer"></canvas>

</template>

<script lang="ts">

import { defineComponent } from 'vue'
import * as d3 from "d3"
import {Chart} from "chart.js"


export default defineComponent({


    data: ()=>{
        return{
            text: "",
        }
    },

    methods:{

        Click(){
            this.text = "Pressed";
            d3.select("#list").selectAll("li").data([10,20,30,40,50]).text(function(d){return d})
            .enter().append("li").text(function(d){return "Dynamically created value" + d;});
        },

        Remove(){
            d3.selectAll("li").data([30,40,50]).exit().remove();
        },

        Draw(){
            var width = 300;
            var height = 300;
            var svg = d3.select("#svgcontainer").append("svg").attr("width",width).attr("height",height);
            svg.append("line").attr("x1",100).attr("y1",100).attr("x2",200).attr("y2",200).style("stroke", "rgb(255,255,0)")
            .style("stroke-width", 2);

            
        },

   

    }


});



</script>


<style>
</style>