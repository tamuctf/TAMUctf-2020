<?php
$address = "localhost";
$user = "webserver";
$password = "wBUs?kWKvXDV?V%xQwj^=xqZGL*29wGP";
$db = "db";

if( isset($_POST['username']) && isset($_POST['password'])) {
    
    $connection = new mysqli($address, $user, $password, $db);
    if ($connection->connect_error) {
        die("Connection failed: " . $connection->connect_error);
    }

    $login_user = $_POST['username'];
    $login_pass = $_POST['password'];

    $sql = "SELECT * FROM accounts WHERE username='$login_user' AND password='$login_pass'";
    $result = $connection->query($sql);

    if($result->num_rows == 1) {
        echo "You've successfully authorized, but that doesn't get you the password.  ";
    } else {
        echo "Invalid login info.  ";
    }
    $connection->close();
} else {
    echo "Both username and password must be entered.  ";
}
?>