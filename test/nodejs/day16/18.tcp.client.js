/**
 * Created by KICT-04 on 2016-07-19.
 */
const net = require('net');

const ip = 'localhost';
const PORT = 8080;

let socket = new net.Socket();

socket.connect(PORT,ip,()=> {
    console.log("connect to: " + ip + PORT);
    socket.write("hello");
});

socket.on('data',(evt)=>{
    console.log(String(evt));
});

socket.on('error',(evt)=>{
    console.log(evt);
});

socket.on('close',(evt)=>{
    console.log(evt.toString());
});