<?php
header("Content-Type: text/html");
echo "<html><head><title>CGI Test</title></head>";
echo "<body>";
echo "<h1>CGI Test Successful!</h1>";
echo "<p>Server: " . $_SERVER['SERVER_NAME'] . "</p>";
echo "<p>Request Method: " . $_SERVER['REQUEST_METHOD'] . "</p>";
echo "<p>Request URI: " . $_SERVER['REQUEST_URI'] . "</p>";
echo "<p>Query String: " . $_SERVER['QUERY_STRING'] . "</p>";
echo "<p>Current Time: " . date('Y-m-d H:i:s') . "</p>";

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    echo "<h2>POST Data:</h2>";
    echo "<pre>" . file_get_contents('php://input') . "</pre>";
}

echo "</body></html>";
?>