var ffi_i2c = require("ffi_i2c");
var createI2cbus = function(busPtr, address) {
    var _busPtr = busPtr;
    var _add = address;
    var i2c_bus = new Object();

    i2c_bus.write = function() {
        var callback = 0;
        try {
            if (_busPtr <= 0)
                throw new Error('the i2c bus is not opened');

            //判断callback是否存在
            if (arguments.length > 1 && typeof(arguments[1]) == 'function')
                callback = arguments[1];

            //对入参个数进行判断
            if (arguments.length == 0 || arguments.length > 2)
                throw new Error('the count of arguments is uncorrect');

            if (typeof(arguments[0]) == "object" && arguments[0].length > 0) {
                /*创造msg对象，通过i2c_transfer写入*/
                var msgs = new Object(); // msgs创建子属性的顺序不可变动，addr->flags->len->buffer
                msgs.addr = _add; // 由入参定义，不可在子函数内赋值
                msgs.flags = 0; // 0为写，1为读
                msgs.len = 0;
                msgs.buffer = new Buffer(arguments[0]);
                msgs.len = msgs.buffer.length;

                var sendcount = ffi_i2c.i2c_transfer(_busPtr, 1, msgs);

                if (sendcount == 0)
                    throw new Error('send failed');
            } else {
                throw new Error('the type or count of bytes is not correct');
            }

            //执行callback，传回null
            if (typeof(callback) == 'function')
                callback(null);
        } catch (err) {
            //捕获到error后执行callback,传回err
            if (typeof(callback) == 'function')
                callback(err);
        }
    }

    i2c_bus.read = function() {
        var callback = 0;
        var array = 0
        try {
            if (_busPtr <= 0)
                throw new Error('the i2c bus is not opened');

            //判断callback是否存在
            if (arguments.length > 1 && typeof(arguments[1]) == 'function')
                callback = arguments[1];

            //对入参个数进行判断
            if (arguments.length == 0 || arguments.length > 2)
                throw new Error('the count of arguments is uncorrect');

            if (typeof(arguments[0]) == "number") {
                /*创造msg对象，通过i2c_transfer读取*/
                var msgs = new Object(); // msgs创建子属性的顺序不可变动，addr->flags->len->buffer
                msgs.addr = _add; // 由入参定义，不可在子函数内赋值
                msgs.flags = 1; // 0为写，1为读
                msgs.len = arguments[0];
                msgs.buffer = new Buffer(arguments[0])

                var readcount = ffi_i2c.i2c_transfer(_busPtr, 1, msgs);

                if (readcount == 0)
                    throw new Error('read failed');

                //从i2c bus读取数据后，把buffer中的内容转成Arrary
                array = new Array(arguments[0]);
                for (var i = 0; i < arguments[0]; i++)
                //array[i] = [buffer.readUInt8(i)];
                    array[i] = [msgs.buffer.readUInt8(i)];
            } else {
                throw new Error('the type of length is not number');
            }

            //执行callback，传回null
            if (typeof(callback) == 'function')
                callback(null, array);
        } catch (err) {
            //捕获到error后执行callback,传回err
            if (typeof(callback) == 'function')
                callback(err);
        }
    }

    i2c_bus.close = function() {
        var callback = 0;
        try {
            if (_busPtr <= 0)
                throw new Error('the i2c bus is not opened');

            //判断callback是否存在
            if (arguments.length > 0 && typeof(arguments[0]) == 'function')
                callback = arguments[0];

            //对入参个数进行判断
            if (arguments.length > 1)
                throw new Error('the count of arguments is uncorrect');

            _busPtr = 0;

            //执行callback，传回null
            if (typeof(callback) == 'function')
                callback(null);
        } catch (err) {
            //捕获到error后执行callback,传回err
            if (typeof(callback) == 'function')
                callback(err);
        }
    }
    return i2c_bus;
}

var i2c_obj = (function i2c() {
    this.open = function() //open(configuration,[callback])
        {
            var i2cbus_obj = 0;
            var callback = 0;
            try {
                //判断callback是否存在
                if (arguments.length > 1 && typeof(arguments[1]) == 'function')
                    callback = arguments[1];

                //对入参个数进行判断
                if (arguments.length == 0 || arguments.length > 2)
                    throw new Error('the count of arguments is uncorrect');

                //对configuration进行判断
                if (typeof(arguments[0]) == 'object') {
                    if (typeof(arguments[0].device) != "string")
                        throw new Error('the device value of configuration is uncorrect');

                    if (typeof(arguments[0].address) != "number" || arguments[0].address < 0)
                        throw new Error('the device value of configuration is uncorrect');
                } else {
                    throw new Error('the type of configuration is uncorrect');
                }

                var busPtr = ffi_i2c.i2c_find(arguments[0].device); // 查找i2c bus

                if (busPtr < 0)
                    throw new Error('i2c bus named " ' + arguments[0].device + ' " cannot be found');

                i2cbus_obj = createI2cbus(busPtr, arguments[0].address); //创建 i2c bus 对象

                //执行callback，传回null
                if (typeof(callback) == 'function')
                    callback();
                return i2cbus_obj;
            } catch (err) {
                //捕获到error后执行callback,传回err
                if (typeof(callback) == 'function')
                    callback(err);
            }
        }
    return {
        open: open
    }
})()

module.exports = i2c_obj;