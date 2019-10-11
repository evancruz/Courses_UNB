function average (array) {
    return array.reduce((a,b) => a+b , 0)/array.length;
}
console.log(average([1,2,3]));

function average2 (array) {
    let sum=0;
    array.forEach(
        function (a) {
            sum=sum+a;
        }
    );
    return sum/array.length;
}
//
function average3 (array) {
    let sum=0;
    array.forEach((a) => sum = sum + a);
    return sum/array.length;
}
console.log(average3([1,2,3]));

exports.average=average3;