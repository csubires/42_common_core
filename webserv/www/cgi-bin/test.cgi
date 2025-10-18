#!/bin/bash
echo "Content-Type: text/html"
echo ""
echo "<html><body>"
echo "<h1>CGI Script Funcionando</h1>"
echo "<p>Query string: $QUERY_STRING</p>"
echo "<p>Request method: $REQUEST_METHOD</p>"
echo "</body></html>"
