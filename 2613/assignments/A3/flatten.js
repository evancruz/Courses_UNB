let flatten = (arr) => {
   let flattenedArr = [];
   for(let i = 0; i < arr.length; i++){
      if(Array.isArray(arr[i])){
         console.log("array is Array " + flattenedArr);
         flattenedArr = flattenedArr.concat(flatten(arr[i]));
         
      } else {
         console.log("push element " + arr[i]);
         flattenedArr.push(arr[i]);
      }
   }
   return flattenedArr;
}


exports.flatten = flatten;