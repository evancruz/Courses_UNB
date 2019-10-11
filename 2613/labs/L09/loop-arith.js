function plus(a,b) {
    for (var i=0; i < a; i++){
        b++;
    }
    return b;
}

function mult(a,b) {
    sum=0;
    for (let i=0; i<a; i++){
        sum = plus(sum, b);
    }
    return sum;
}



/*function plus(a,b) {
    if (a === 0) {
        return b;
    } else {
        return plus(a-1, b+1);
    }
}

function mult(a,b) {
    if (a===0) {
        return 0;
    } else {
        plus(mult(a-1, b), b);
    }
}
*/
//key value pair
exports.plus = plus;
exports.mult = mult;

