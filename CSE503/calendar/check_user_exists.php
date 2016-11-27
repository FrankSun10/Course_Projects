<?php
// valid web security
ini_set("session.cookie_httponly", 1);
session_start();
$previous_ua = @$_SESSION['useragent'];
$current_ua = $_SERVER["HTTP_USER_AGENT"];
if(isset($_session['useragent']) && $previous_ua != $current_ua){
    die("Session Hijack dectected");
}else{
    $_SESSION['useragent'] = $current_ua;
}
header("Content-Type: application/json");// set the MIME type to application/json to send a json response
require "database.php";

$token = htmlentities($_POST['token']);

// verify token value
if($_SESSION['token'] != trim($_POST['token'])){
    echo json_encode(array(
       "success"=>false,
       "message" => "token mismatch",
    ));
    die("Request forgery detected");
}

//check if user exists
$added_username = $_POST['new-group-username'];
$query = $mysqli->prepare("select count(*) from users where username=?");
if($query){
    $query->bind_param("s", $added_username);
    $query->execute();
    $query->bind_result($num_rows);
    $query->fetch();
    if($num_rows == 1){
        echo json_encode(array(
            "success" => true
        ));
    }
    else{
        echo json_encode(array(
            "success" => false,
            "message" => "Error: user does not exist"
        ));
    }
}
else{
    echo json_encode(array(
        "success" => false,
        "message" => "Could not access database"
    ));
}
?>