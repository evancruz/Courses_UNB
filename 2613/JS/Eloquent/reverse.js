let revArray = (arr) => {
//takes an array as argument and produces a new array that has the same elements in the inverse order.
   let reversedArr =[];
   for(let i = arr.length-1; i >= 0; i--){
      reversedArr.push(arr[i]);
   }
   return reversedArr;
}
/*      3-3 = 0 
2 - 1 = 1
1 + 1= 2
0 + 3 = 3*/

let arr1 = [0, 1, 2, 3];
console.log(revArray(arr1));

