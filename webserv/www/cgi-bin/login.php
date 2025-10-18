<?php
session_start();

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'] ?? '';
    $password = $_POST['password'] ?? '';

    // Validación simple (en producción usar hash seguro)
    if ($username === 'admin' && $password === 'password') {
        $_SESSION['user_id'] = 1;
        $_SESSION['username'] = $username;
        $_SESSION['logged_in'] = true;

        echo "Content-Type: application/json\r\n\r\n";
        echo json_encode(['success' => true, 'message' => 'Login successful']);
    } else {
        echo "Content-Type: application/json\r\n\r\n";
        echo json_encode(['success' => false, 'message' => 'Invalid credentials']);
    }
} else {
    echo "Content-Type: text/html\r\n\r\n";
    ?>
    <html>
    <body>
        <h1>Login</h1>
        <form method="POST">
            <input type="text" name="username" placeholder="Username" required>
            <input type="password" name="password" placeholder="Password" required>
            <button type="submit">Login</button>
        </form>
    </body>
    </html>
    <?php
}
?>
