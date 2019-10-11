let read_json_file=require("./read_json_file.js").read_json_file;

let data = null;

function by_name(name){
    if (data===null)
        data=read_json_file("ancestry.json");
    // simple linear scan
    for(let i = 0; i<data.length; i++){
        let current_name = data[i].name;
        if(current_name === name)
            return data[i];
    }
    return null;

}
exports.by_name=by_name;