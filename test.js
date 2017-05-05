var serialport = require("serialport");
var portName = process.argv[2];

var myPort = new serialport(portName,{
  baudRate : 9600,
  parser:serialport.parsers.readline("\r\n")
});

myPort.on('open',onOpen);
myPort.on('data',onData);

function onOpen(){
  console.log("Open Connection");
}

function onData(data){
  console.log(data);
  // console.log(data.water)
}