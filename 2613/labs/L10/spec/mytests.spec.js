let deepEqual=require("../equal.js").dE;
//equiv to ..

//let equal = require("../equal.js");
//let deepEqual=equal.deepEqual;

let array = require("../arrays.js").range;
let sum = require("../arrays.js").sum;

describe("equal", function () {
    let obj = {here: {is: "an"}, object: 2};
    it("self", function () {
        expect(deepEqual(obj,obj)).toBe(true);
    });

    it("null", function () {
        expect(deepEqual(null,null)).toBe(true);
    });

    it("different", function () {
        expect(deepEqual(obj, {here: 1, object: 2})).toBe(false);
    });

    it("more keys in A", function () {
        expect(deepEqual({x:1, y:2, z:3}, {x:1, y:2})).toBe(false);
    });

    it("equivalent", function () {
        expect(deepEqual(obj, {here: {is: "an"}, object: 2})).toBe(true);
    });
});



describe("range", function () {
    it("empty", function () {
        expect(array(2,1)).toEqual([]);
    });

    it("single", function () {
        expect(array(2,2)).toEqual([2]);
    });

    it("multiple", function () {
        expect(array(42,50)).toEqual([42,43,44,45,46,47,48,49,50]);
    });
});


describe("sum", function () {
    it("empty", function () {
        expect(sum([])).toBe(0);
    });

    it("single", function () {
        expect(sum([2])).toBe(2);
    });

    it("multiple", function () {
        expect(sum(array(1,10))).toBe(55);
    });    
});

