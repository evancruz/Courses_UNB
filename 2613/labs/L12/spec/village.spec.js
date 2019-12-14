const village = require("../village.js");


describe("roadGraph",
    function() {
        let roadGraph=village.roadGraph;
        it("Alice's neighbors",
            function() {
                expect(roadGraph["Alice's House"].sort()).toEqual(["Bob's House", "Cabin", "Post Office"]);
            });

        it("Bob's neighbors",
            function() {
                expect(roadGraph["Bob's House"]).toEqual(jasmine.objectContaining(["Alice's House"]));
            });
    });

const VillageState = village.villageState;

describe("Village State",
    function() {
        let first = new VillageState(
            "Post Office",
            [{place: "Post Office", address: "Alice's House"}, {place: "Mars", address: "Jupiter"}]
        );
        let next = first.move("Alice's House");
        it("move changes place",
            function() {
                expect(next.place).toEqual("Alice's House");
            });
            
        it("parcel is delivered",
            function() {
                expect(next.parcels).toEqual([{place: "Mars", address: "Jupiter"}]);
            });

        it("move does not modify",
            function() {
                expect(first.place).toEqual("Post Office");
            });

        it("invalid destination",
            function() {
                expect(first.move("Mars")).toBe(first);
            });
    });

describe("runRobot",
    function() {
        it("no parcels",
            function() {
                console.log = jasmine.createSpy("log");
                noParcels = new VillageState("Post Office",[]);
                village.runRobot(noParcels);

                expect(console.log).toHaveBeenCalledWith("Done in 0 turns");
            });

        it("random Robot",
            function() {
                console.log=jasmine.createSpy("log");
                village.runRobot(VillageState.random(),
                    village.randomRobot);

                expect(console.log).toHaveBeenCalledWith(jasmine.stringMatching(""));
            });
    });


