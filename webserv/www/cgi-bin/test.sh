#!/bin/bash

echo "Content-Type: text/html"
echo ""  # Empty line to separate headers from body

echo "<html><head><title>Shell CGI Test</title></head>"
echo "<body>"
echo "<h1>Shell CGI Test Successful!</h1>"
echo "<p>Server: $SERVER_NAME</p>"
echo "<p>Request Method: $REQUEST_METHOD</p>"
echo "<p>Request URI: $REQUEST_URI</p>"
echo "<p>Query String: $QUERY_STRING</p>"
echo "<p>Current Date: $(date)</p>"

if [ "$REQUEST_METHOD" = "POST" ]; then
    echo "<h2>POST Data:</h2>"
    echo "<pre>"
    cat
    echo "</pre>"
fi

echo "</body></html>"