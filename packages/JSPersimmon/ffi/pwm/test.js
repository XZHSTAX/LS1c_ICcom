var pwm = require("pwm.js");

var open_callback = function(err) {
    if (err)
        console.log(" open err : " + err.message)
    console.log("open callback has been done!");
}

var set_callback = function(err) {
    if (err)
        console.log(" set err : " + err.message)
    console.log("set callback has been done!");
}

var enable_callback = function(err) {
    if (err)
        console.log(" enable err : " + err.message)
    console.log("enable callback has been done!");
}

var close_callback = function(err) {
    if (err)
        console.log(" close err : " + err.message)
    console.log("close callback has been done!");
}

var pwmpin = pwm.open("pwm1", open_callback);
var configuration = {
    channel: 1,
    period: 1000000000, //1秒
    pulse: 300000000 //0.3秒
}
pwmpin.setConfig(configuration, set_callback);
pwmpin.setEnable(false, enable_callback);
pwmpin.close(close_callback);