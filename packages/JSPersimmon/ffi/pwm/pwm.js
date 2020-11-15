var ffi_pwm = require("ffi_pwm");
var createPWMPin = function(pinPtr) {
    var _pinPtr = pinPtr;

    /* configuration */
    var _channel = 0;
    var _period = 0;
    var _pulse = 0;

    var hasSet = false;

    var pwm_pin = new Object();
    pwm_pin.setConfig = function() { //setConfig(channel,period,pulse,[callback])
        console.log("pwm_pin.setConfig >>");
        var callbak = 0;
        try {
            if (_pinPtr <= 0)
                throw new Error('the pwm pin is not opened');

            //判断callback是否存在
            if (arguments.length > 1 && typeof(arguments[1]) == 'function')
                callback = arguments[1];

            //对入参个数进行判断
            if (arguments.length == 0 || arguments.length > 2)
                throw new Error('the count of arguments is uncorrect');

            console.log("typeof(arguments[0])  :" + typeof(arguments[0]))
                //对configuration入参进行判断
            if (typeof(arguments[0]) != "object")
                throw new Error('the type of configuration is uncorrect');

            //对configuration.channel入参进行判断
            if (typeof(arguments[0].channel) == "number" && arguments[0].channel > 0) {
                _channel = arguments[0].channel;
            } else {
                throw new Error('the value of channel is uncorrect');
            }
            //对configuration.period入参进行判断 1ns ~ 4.29s
            if (typeof(arguments[0].period) == "number" &&
                arguments[0].period > 0 &&
                arguments[0].period < 4290000000) {
                _period = arguments[0].period;
            } else {
                throw new Error('the value of period is uncorrect');
            }
            //对configuration.pulse入参进行判断 1ns ~ period
            if (typeof(arguments[0].pulse) == "number" &&
                arguments[0].pulse > 0 &&
                arguments[0].pulse < _period) {
                _pulse = arguments[0].pulse;
            } else {
                throw new Error('the value of pulse is uncorrect');
            }

            //根据选项设定 pwm pin
            var ret = ffi_pwm.pwm_set(_pinPtr, _channel, _period, _pulse);
            if (ret == 0)
                hasSet = true;

            //执行callback，传回null
            if (typeof(callback) == 'function')
                callback(null);
        } catch (err) {
            hasSet = false;
            //捕获到error后执行callback,传回err
            if (typeof(callback) == 'function')
                callback(err);
        }
    }

    pwm_pin.setEnable = function() { //setEanble(enable,[callback])
        var callbak = 0;
        try {
            if (_pinPtr <= 0)
                throw new Error('the pwm pin is not opened');

            //判断callback是否存在
            if (arguments.length > 1 && typeof(arguments[1]) == 'function')
                callback = arguments[1];

            //对入参个数进行判断
            if (arguments.length == 0 || arguments.length > 2)
                throw new Error('the count of arguments is uncorrect');

            //判断configuration是否已经设定完毕
            if (hasSet == false)
                throw new Error('the configuration has not been set successfully');

            // 开/关 pwm
            if (typeof(arguments[0]) == "boolean") {
                if (arguments[0] == true)
                    ffi_pwm.pwm_enable(_pinPtr, _channel);
                else
                    ffi_pwm.pwm_disable(_pinPtr, _channel);
            } else
                throw new Error('the type of enable is not boolean');

            //执行callback，传回null
            if (typeof(callback) == 'function')
                callback(null);
        } catch (err) {
            //捕获到error后执行callback,传回err
            if (typeof(callback) == 'function')
                callback(err);
        }
    }

    pwm_pin.close = function() { //close([callback])
        var callbak = 0;
        try {
            if (_pinPtr <= 0)
                throw new Error('the pwm pin is not opened');

            //判断callback是否存在
            if (arguments.length > 0 && typeof(arguments[0]) == 'function')
                callback = arguments[0];

            //对入参个数进行判断
            if (arguments.length > 1)
                throw new Error('the count of arguments is uncorrect');

            _pinPtr = 0;

            //执行callback，传回null
            if (typeof(callback) == 'function')
                callback(null);
        } catch (err) {
            //捕获到error后执行callback,传回err
            if (typeof(callback) == 'function')
                callback(err);
        }
    }
    return pwm_pin;
}

var pwm_obj = (function pwm() {
    this.open = function() //open(configuration,[callback])
        {
            var pwmpin_obj = 0;
            var callback = 0;
            try {
                //判断callback是否存在
                if (arguments.length > 1 && typeof(arguments[1]) == 'function')
                    callback = arguments[1];

                //对入参个数进行判断
                if (arguments.length == 0 || arguments.length > 2)
                    throw new Error('the count of arguments is uncorrect');

                //对name进行判断
                if (typeof(arguments[0]) != 'string') {
                    throw new Error('the type of name is uncorrect');
                }

                var pinPtr = ffi_pwm.pwm_find(arguments[0]); // 查找pwm pin

                if (pinPtr < 0)
                    throw new Error('pwm pin named " ' + arguments[0] + ' " cannot be found');

                pwmpin_obj = createPWMPin(pinPtr); //创建 pwm pin 对象

                //执行callback，传回null
                if (typeof(callback) == 'function')
                    callback();
                return pwmpin_obj;
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

module.exports = pwm_obj;