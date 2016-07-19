/**
 * Created by KICT-04 on 2016-07-19.
 */

const net = require('net');
const PORT = 8080;

net.createServer((socket)=> {
    console.log('connect :' + socket.remoteAddress + ':' + socket.remotePort);

    socket.on('error',(evt)=>{
       console.log(evt);
    });

    socket.on('close',(evt)=>{
        console.log('connetion closed!')
        console.log(evt);
    });

    socket.on('data',(evt)=> {
        socket.write("누구세요?");
        console.log(evt.toString());
    });

}).listen(PORT);

console.log('server listem :' + PORT);