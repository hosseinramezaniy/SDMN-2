from http.server import HTTPServer,BaseHTTPRequestHandler

Host = "0.0.0.0"
Port = 8000

class MyHTTPServer(BaseHTTPRequestHandler):
    Flag = True
    def do_GET(self):
        if MyHTTPServer.Flag == True :
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.end_headers()
            self.wfile.write(bytes("{\"status\":\"ok\"}","utf-8"))
        else :
            self.send_response(201)
            self.send_header("Content-Type", "application/json")
            self.end_headers()
            self.wfile.write(bytes("{\"status\":\"not ok\"}","utf-8"))
    def do_POST(self):
        self.send_response(201)
        self.send_header("Content-Type","application/json")
        self.end_headers()
        self.wfile.write(bytes("{\"status\":\"not ok\"}","utf-8"))
        MyHTTPServer.Flag = not MyHTTPServer.Flag

server = HTTPServer((Host,Port), MyHTTPServer)
print("Server now running ..")
server.serve_forever()
server.server_close()
print("Server stopped!")
