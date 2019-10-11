let flatten = (array) => {
    return array.reduce((acc,cur) => acc.concat(cur),[]);  
};

//acc=acc.concat(current); -> within a loop
//reduce -> itereates over the array and calls whatever function is passed in 

exports.flatten=flatten;
