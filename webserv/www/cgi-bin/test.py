#!/usr/bin/python3

import os
import sys

print("Content-Type: text/html")
print()  # Empty line to separate headers from body

print("<html><head><title>Python CGI Test</title></head>")
print("<body>")
print("<h1>Python CGI Test Successful!</h1>")
print(f"<p>Server: {os.environ.get('SERVER_NAME', 'Unknown')}</p>")
print(f"<p>Request Method: {os.environ.get('REQUEST_METHOD', 'Unknown')}</p>")
print(f"<p>Request URI: {os.environ.get('REQUEST_URI', 'Unknown')}</p>")
print(f"<p>Query String: {os.environ.get('QUERY_STRING', 'Unknown')}</p>")

if os.environ.get('REQUEST_METHOD') == 'POST':
    print("<h2>POST Data:</h2>")
    post_data = sys.stdin.read()
    print(f"<pre>{post_data}</pre>")

print("</body></html>")