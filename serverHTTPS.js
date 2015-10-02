//How to run
//Open command line and run form the project directory:
//>node server.js

var http = require("https");
var path = require('path');
//WireShark sees TLS packets  only from 443 port
var port = 9001; 
var fs = require('fs');
var certsPath = path.join(__dirname, 'certs', 'server');

options = 
{
  key: fs.readFileSync(path.join(certsPath, 'privateKey.pem'))
, cert: fs.readFileSync(path.join(certsPath, 'server.pem'))
, rejectUnauthorized: true
}

function handle_request(request, response)
{
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
var server = http.createServer(options, handle_request).listen(port);
console.log("Start listening on port %d", port);