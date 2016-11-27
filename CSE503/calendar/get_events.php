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

// check loged in
if(!isset($_SESSION['username'])){
    echo json_encode(array(
       "success"=>false,
       "message" => "Not loging in"
    ));
    exit;
}

// verify token value
if($_SESSION['token'] != trim($_POST['token'])){
    echo json_encode(array(
       "success"=>false,
       "message" => "token dismatch"
    ));
    die("Request forgery detected");
}
//prepare the events database
$owner = $_SESSION['username'];
$date = htmlentities($_POST['date']);
$get_events = $mysqli->prepare("select content, id, category from events where owner = ? and date = ?");
if(!$get_events){
        $get_events_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success"=> false,
            "message" => "database error"
        ));
        exit;
}

$get_events->bind_param("ss", $owner, $date);
$get_events->execute();
$get_events_result= $get_events->get_result();
$event_array = array();
$i =0;
while($row = $get_events_result->fetch_assoc()){
    $event_array[$i] = $row;
    $i++;
}
// pass an array of events to javascript
$get_events->close();

echo json_encode(array(
   "success"=>true,
   "message" => "Successfully get events",
   "event_array"=>$event_array
));











?>