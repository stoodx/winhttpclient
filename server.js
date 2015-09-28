//How to run
//Open command line and run form the project directory:
//>node server.js

var http = require("http");
var port = 9000;
function handle_request(request, response){
	console.log("%s request to %s", request.method, request.url);
	 if (request.method == 'POST') {
        var body = '';
        request.on('data', function (data) {
            body += data;

            // Too much POST data, kill the connection!
            if (body.length > 1e6)
                request.connection.destroy();
			console.log("Retrieved data %s", body);
        });
		}
	response.end("It works");
}
var server = http.createServer(handle_request).listen(port);
console.log("Start listening on port %d", port);