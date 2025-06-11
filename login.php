<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = $_POST['Username'] ?? '';
    $password = $_POST['Password'] ?? '';

    if (empty($username) || empty($password)) {
        echo "Please enter valid username and password."
    } else {
        if ($username == "admin" && $password == "password") {
            echo "Correct account and password."
        }
        else {
            echo "Wrong account or password."
        }
    }
} else {
    echo "Can't receive POST data."
}


?>