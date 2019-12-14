let person = require("../Person.js");

describe("person",
    function () {
        let bob=new Person("bob", 42);
        it("constructor",
            function () {
                expect(bob.name).toEqual("bob");
                expect(bob.age).toEqual(42);
            });

        it("birthday does not mutate",
            function (){
                let newbob = bob.birthday();

                expect(bob.age).toEqual(42);
                expect(newbob.age).toEqual(43);
            });
             
    });

describe("people",
    function () {
        let people = new People("ancestry.json");
        it("read all records",
            function () {
                expect(people.length).toEqual(10);
            });

        it("hash table",
            function () {
                expect(people["Clara Aernoudts"]).toEqual(new Person("Clara Aernoudts", 95));
            });
    });