import * as d3 from "d3";
import { csv } from "d3-fetch";
import {DSVRowArray, DSVRowString} from "d3-dsv";
import { loadavg } from "os";
export default class DataManager{

    private _dataframe : DSVRowArray = new Object() as any;
    private _loaded : boolean = false;
    constructor(){
       
    }

    public Load(csvUri : string): Promise<void>{
        this._dataframe = new Object() as any;
        return csv(csvUri).then((result)=>{
            this._dataframe = result;
            this._loaded = true;
        });
    }

    public Loaded():boolean{
        return this._loaded;
    }

    public DataFrame(): DSVRowArray{
        if(this._loaded){
            return this._dataframe;
        }
        return new Object() as any;
    }

    public GetYear(year: number) : Array<object>{
        var data : Array<object>= new Array();
        this._dataframe.map((row)=>{
            if(parseInt(row["year"] as string) == year){
                data.push(row);
            }
        })
        return data;
    }


    public GetCountry(country : string): Array<DSVRowString>{
        var data: Array<DSVRowString> = new Array();
        this._dataframe.map((row : any)=>{
            if(row["country"] == country){
                data.push(row);
            }
        });
        return data;
    }
    
    
}