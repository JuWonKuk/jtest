/**
 * Created by KICT-04 on 2016-07-15.
 */
const http = require('http');

const server = http.createServer(function(req,res) {
    res.statusCode = 200;
    res.setHeader("Content-Type","text/html");
    res.end("<h1> hello world Ju Won Kuk </h1>");
});

server.listen(8081,function () {
    console.log("http server start");
});
