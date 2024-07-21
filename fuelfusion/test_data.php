<?php

$hostname = "localhost";
$username = "root";
$password = "";
$dbname = "sensor_db";

$conn = mysqli_connect($hostname, $username, $password, $dbname);

if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

echo "Connected successfully";

if(isset($_POST['volume'])){

    $v = $_POST['volume'];

    $sql = "INSERT INTO hcsr04 (volume) values (".$v.")";

    if (mysqli_query($conn, $sql)) {
        echo "New record created successfully";
    } else {
        echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }
}

?>