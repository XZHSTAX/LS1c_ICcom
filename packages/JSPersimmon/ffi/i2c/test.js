var i2c = require("i2c.js");

var open_callback = function(err) {
    if (err)
        console.log(" open err : " + err.message)
    console.log("open callback has been done!");
}

var read_callback = function(err, arrary) {
    if (err)
        console.log(" read err : " + err.message);
    if (arrary)
        for (var i = 0; i < arrary.length; i++)
            console.log("arrary[ " + i + " ] : " + arrary[i]);
    console.log("read callback has been done!");
}
var write_callback = function(err) {
    if (err)
        console.log(" write err : " + err.message)
    console.log("write callback has been done!");
}
var i2cbus = i2c.open({
        device: "i2c1",
        address: 0X68
    },
    open_callback
)

var arr = [0X41];
//console.log("js >> str : " + str);
i2cbus.write(arr, write_callback);
i2cbus.read(2, read_callback);