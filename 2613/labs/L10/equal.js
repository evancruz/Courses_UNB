let deepEqual = (a, b) => {
    //check null first
    if(a === null && b === null){
        return true;
    } else if (a === null || b === null){
        return false;
    }
        
        
    if(typeof(a) === "object" && typeof(b) === "object") {
        for(let prop in a) {
            if(!(prop in b))
                return false;
            if(!(prop in b) || !(deepEqual(a[prop],b[prop])))
                return false;
        }
        return true;
    } else {
        return (a === b);
    }
};
exports.dE= deepEqual;
//a = {}