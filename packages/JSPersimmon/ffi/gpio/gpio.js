var ffi_gpio = require("ffi_gpio");
var e = require("event");
var createGpiopin = function (pin)
{
	var _pin = pin;
	var obj = new Object();
	e.EventEmitter(obj);
	
	obj.write = function() //write(value,[callback])
	{
		var callback =0;
		try{
			if(_pin <0)
				throw new Error('the GpioPin is not opened');
			
			//判断callback是否存在
			if(arguments.length >1 && typeof(arguments[1]) == 'function')
				callback = arguments[1];
			
			//对入参个数进行判断
			if(arguments.length ==0 || arguments.length > 2)
				throw new Error('the count of arguments is uncorrect');
			
			var setIn = 0;	// 写入Pin的值
			if(typeof(arguments[0]) == "number")
			{
				if(arguments[0] != 0)
					setIn = 1;
			}
			else if(typeof(arguments[0]) == "boolean")
			{
				if(arguments[0] == true)
					setIn =1;
			}
			else
				throw new Error('the type of value is uncorrect');
			
			var before = ffi_gpio.pin_read(_pin);
			console.log("before : " + before);
			
			ffi_gpio.pin_write(_pin,setIn);
			console.log("setIn : " + setIn);
			var after = ffi_gpio.pin_read(_pin);
			console.log("after : " + after);
			if(after != setIn)
				throw new Error('write fail');
			
			if(after != before)
				this.emit("change",after)
			
			//执行callback，传回null
			if(typeof(callback) == 'function')
				callback();
		}catch(err)
		{
			//捕获到error后执行callback,传回err
			if(typeof(callback) == 'function')
				callback(err);
		}
	}
	obj.read = function()
	{
		var callback =0;
		try{
			if(_pin <0)
				throw new Error('the GpioPin is not opened');
			
			//判断callback是否存在
			if(arguments.length >0 && typeof(arguments[0]) == 'function')
				callback = arguments[0];
			
			//对入参个数进行判断
			if(arguments.length > 1)
				throw new Error('the count of arguments is uncorrect');
			
			var ret = ffi_gpio.pin_read(_pin)
			//执行callback，传回null,ret
			if(typeof(callback) == 'function')
				callback(null,ret);
			return ret;
		}catch(err)
		{
			//捕获到error后执行callback,传回err
			if(typeof(callback) == 'function')
				callback(err,null);
		}
		
	}
	obj.close = function()
	{
		console.log("ready to close")
		var callback =0;
		try{
			if(_pin <0)
				throw new Error('the GpioPin is not opened');

			//判断callback是否存在
			if(arguments.length >0 && typeof(arguments[0]) == 'function')
				callback = arguments[0];
			//对入参个数进行判断
			if( arguments.length > 1)
				throw new Error('the count of arguments is uncorrect');
			_pin = -1;
		}catch(err)
		{
			//捕获到error后执行callback,传回err
			if(typeof(callback) == 'function')
				callback(err);
		}
		
	}
	obj.onchanged = function(callback)
	{
		if(typeof(callback) == "function")
			this.on("change",callback);
	}
	return obj;
}

var obj =(function gpio()
{
	this.MODE = {
			OUTPUT : 0,
			INPUT: 1,
			INPUT_PULLUP: 2,
			INPUT_PULLDOWN: 3,
			OUTPUT_OPENDRAIN: 4
	};
	this.open = function() //open(value,[callback])
	{
		var gpiopin_obj = 0;
		var callback = 0
		try{
			//判断callback是否存在
			if(arguments.length >1 && typeof(arguments[1]) == 'function')
				callback = arguments[1];
			
			//对入参个数进行判断
			if(arguments.length ==0 || arguments.length > 2)
				throw new Error('the count of arguments is uncorrect');
			
			//对configuration进行判断
			if(typeof(arguments[0]) == 'object')
			{
				// 对 pin number 进行入参判断
				if(typeof(arguments[0].pin)!="number" || arguments[0].pin < 1 )
					throw new Error('the pin value of configuration is uncorrect');
					var _pin = arguments[0].pin;
				
				// 对 mode 进行入参判断
				if(typeof(arguments[0].mode) == "undefined")
				{
					ffi_gpio.pin_mode(_pin,0);
				}
				else{
					switch(arguments[0].mode)
					{
						case this.MODE.OUTPUT:
							ffi_gpio.pin_mode(_pin,0);
							break;
						case this.MODE.INPUT:
							ffi_gpio.pin_mode(_pin,1);
							break;
						case this.MODE.INPUT_PULLUP:
							ffi_gpio.pin_mode(_pin,2);
							break;
						case this.MODE.INPUT_PULLDOWN:
							ffi_gpio.pin_mode(_pin,3);
							break;
						case this.MODE.OUTPUT_OPENDRAIN:
							ffi_gpio.pin_mode(_pin,4);
							break;
						default:
							throw new Error('the value of mode is uncorrect');
							break;
					}
				}	
			}else{
				throw new Error('the type of pin number is uncorrect');
			}
			
			gpiopin_obj = createGpiopin(arguments[0].pin);

			//执行callback，传回null
			if(typeof(callback) == 'function')
				callback();
			
			return gpiopin_obj;
		}catch(err)
		{
			//捕获到error后执行callback,传回err
			if(typeof(callback) == 'function')
				callback(err);
		}
	}

	return {
		open : open,
		MODE : MODE
	}
})()

module.exports = obj;
