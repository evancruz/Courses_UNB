let fs = require('fs');

class Person{
   constructor(name, age){
      this.name = name
      this.age = age
   }

   birthday(){
      return new Person(this.name, this.age + 1)
   }
}

class People{
   constructor(fileName){
      // read file to get length
      let contents = fs.readFileSync(fileName);
      contents = JSON.parse(contents)
   

      let len = 0
      let names = [];
      for (const entry of contents) {
         let age = (entry.died - entry.born) + 1
         let name = entry.name
         this[name]= new Person(entry.name, age)
         len++
      }
      
      this.length = len
   }

} 
// { "name": "Clara Aernoudts", "sex": "f", "born": 1918, "died": 2012, "father": "Henry Aernoudts", "mother": "Sidonie Coene" },

people = new People("ancestry.json")
console.log(people["length"])
console.log(people["Clara Aernoudts"])

console.log("new Person")
clara = new Person("Clara Aernoudts", 95)
console.log(clara)

//       expect(people["Clara Aernoudts"]).toEqual(new Person("Clara Aernoudts", 95));