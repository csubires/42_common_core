#!/usr/bin/env python3

import os
import cgi

print("Content-Type: text/html")
print("")

print("<html><head><title>Python CGI Test</title></head>")
print("<body>")
print("<h1>Python CGI Test from Root Directory!</h1>")

query_string = os.environ.get('QUERY_STRING', '')
print("<h2>Query String:</h2>")
print("<p>%s</p>" % query_string)

if query_string:
    print("<h2>Parsed Parameters:</h2>")
    form = cgi.FieldStorage()
    for key in form.keys():
        print("<p>%s = %s</p>" % (key, form.getvalue(key)))
else:
    print("<p>No query parameters</p>")

print("<h2>Environment Variables:</h2>")
print("<p>SCRIPT_NAME: %s</p>" % os.environ.get('SCRIPT_NAME', ''))
print("<p>SCRIPT_FILENAME: %s</p>" % os.environ.get('SCRIPT_FILENAME', ''))
print("<p>REQUEST_URI: %s</p>" % os.environ.get('REQUEST_URI', ''))
print("<p>QUERY_STRING: %s</p>" % os.environ.get('QUERY_STRING', ''))

print("</body></html>")
