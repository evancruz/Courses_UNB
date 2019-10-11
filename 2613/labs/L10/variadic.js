function brag(name,...args){
    console.log(name + " has");
    for (let i=0; i<args.length; i++) {
        console.log("\t"+args[i]);
    }
}

brag("attile", "throne of gold", "nice horse", "inlayed bow");

function win(person,thing="a brick"){
    console.log(person + " won " + thing);
}

console.log(win("nick"));
console.log(win("oprah", "car"));