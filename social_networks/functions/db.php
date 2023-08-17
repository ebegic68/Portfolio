<?php
$hostname = "localhost";
$database = "social_networks";
$username = "root";
$password = "";


$con = mysqli_connect($hostname, $username, $password, $database);
function escape($string){
    global $con;
    return mysqli_real_escape_string($con, $string);
}
function query($query){
    global $con;
    return mysqli_query($con, $query);
}
function confim($result){
    global $con;
    if(!$result){
    die("QUERY FAILED" . mysqli_error($con));
    }
}
