/*
Write a function flatten that produces an array containing all of the elements of all of the nested arrays in an array. For full marks your solution should use recursion. Your function should pass the following jasmine tests
*/

let flatten = (arr) => {
   
   for(let element of arr){
      console.log(element);
   }
}

let nestedArr = [[[1], 2, [3]], 4, [5, 6]];
let normalArr = [5, 8, 9];
console.log("nestedArr");
flatten(nestedArr);
console.log("normalArr");
flatten(normalArr);


exports flatten = flatten;