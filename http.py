import http.server
import socketserver

# Define the server address and port
PORT = 8080

# Set up the handler to serve files from the current directory
Handler = http.server.SimpleHTTPRequestHandler

# Create an HTTP server instance
with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Serving HTTP on port {PORT} (http://localhost:{PORT})...")
    
    # Start the server
    httpd.serve_forever()
