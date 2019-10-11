let range = (start, end) => {
    let arr =[];
    let ind = 0;
    while(start <= end){
        arr[ind] = start;
        ind++;
        start++;
    }
    /*
    for(int i = from; i < ){
        arr.push(i);
    }
    */
    return arr;
};

exports.range = range;

let sum = (arr) => {
    let total = 0;
    for(let i = 0; i < arr.length; i ++){
        total += arr[i];
    }
    return total;
};

exports.sum=sum;