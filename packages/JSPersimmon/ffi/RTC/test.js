var date = require("date.js");

var dateCallback = function(err) {
    if (err)
        console.log(err);
}

var timeCallback = function(err) {
    if (err)
        console.log(err);
}

date.setRtcDate(1988, 2, 31, dateCallback);
date.setRtcTime(13, 70, 70, timeCallback);
var myDate = date.getRtcTime();

console.log("myDate : " + myDate);