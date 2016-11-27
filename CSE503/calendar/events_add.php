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
header("Content-Type: application/json");// set the MIME type to application/jason to send a json response
require "database.php";

$date = htmlentities($_POST['date']);
$content = htmlentities($_POST['content']);
$token = htmlentities($_POST['token']);
$category = htmlentities($_POST['category']);

// verify token value
if($_SESSION['token'] != trim($_POST['token'])){
    echo json_encode(array(
       "success"=>false,
       "message" => "token dismatch",
    ));
    exit;
    //die("Requsest forgery detected");
}

$add_event = $mysqli->prepare("insert into events (owner, date, content, category) values (?,?,?,?)");
if(!$add_event){
        $add_event_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success"=> false,
            "message" => $add_event_message
            ));
        exit;
}
$add_event->bind_param("ssss", $_SESSION['username'], $date, $content, $category);
$add_event->execute();
$add_event->close();

// success message
echo json_encode(array(
   "success"=>true,
   "message" => "Successfully added"
));
?>