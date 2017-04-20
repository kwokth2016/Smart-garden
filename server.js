var express = require('express');
var app = express();
var server = require('http').createServer(app);
var io = require('socket.io')(server);
var path = require("path");
var serialport = require("serialport");
var util = require("util");

app.use(express.static(__dirname + '/'));

//eg type node server.js COM3
var portName = process.argv[2];
var myPort = new serialport(portName,{
  baudRate : 9600,
  parser:serialport.parsers.readline("\n")
});

var dataBegin;
var line = "";

myPort.on('open',function(err){
  if(err){
    console.log(err);
  }
  console.log('Serial connected');
  myPort.on('data',function(data){
    line = util.inspect(JSON.parse(data));
    console.log(line);
    io.emit("Data is ready", line.replace("\"", ""));
  });
});

io.on("connection", function(socket) {
    console.log("User connected");
});

app.get('/', function(req, res){
    res.sendfile('index.html');
});


const port = process.env.PORT || 3000;

server.listen(port);
console.log(`Server listening on http://localhost:${port}`);