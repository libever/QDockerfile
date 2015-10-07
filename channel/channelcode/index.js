#!/nodejs/bin/node

var app = require("express")();
var http = require('http').Server(app);

var io = require('socket.io')(http);
//"you can find client script on url : /socket.io/socket.io.js"

io.on("connection",function(socket){
	console.log("user connnected ....");
	socket.on("disconnect",function(){
		console.log("user leave ....");
	});
	socket.on("hello world",function(data){
		console.log("message get : " + data);

		//全局广播，信息
		io.emit('this', { will: 'be received by everyone'});

	});
});

app.get("/",function(request,response){
	//response.send("<h1>Hello world</h1>");
	response.sendFile(__dirname + "/a.html");
});

http.listen(9001, function(){
  console.log('listening on *:9001');
});

