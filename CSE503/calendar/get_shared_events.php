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

// verify token value
if($_SESSION['token'] != trim($_POST['token'])){
    echo json_encode(array(
       "success"=>false,
       "message" => "token dismatch"
    ));
    exit;
    //die("Requsest forgery detected");
}

// these two parameters are only used for get_shared_evnts_daily function in function.js
$owner = htmlentities($_POST['owner']);
$date = htmlentities($_POST['date']);

// connect to database
$get_shared_events = $mysqli->prepare("select * from sharedevents");
if(!$get_shared_events){
        $get_shared_events_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success"=> false,
            "message" => $get_shared_events_message
        ));
        exit;
}

$get_shared_events->execute();
$get_shared_events_result= $get_shared_events->get_result();
$shared_events_array = array();
$i =0;
while($row = $get_shared_events_result->fetch_assoc()){
    $shared_events_array[$i] = $row;
    $i++;
}
// pass an array of events to javascript
$get_shared_events->close();

if(empty($owner)){
    echo json_encode(array(
        "success"=>true,
        "message" => "Successfully get the shared events",
        "shared_events_array" => $shared_events_array
    ));
    exit;
}

//get shared events from a particular owner to a particular user
$get_particular_events = $mysqli->prepare("select * from sharedevents where owner = ? and sharedto = ? and date = ?");
if(!$get_particular_events){
        $get_particular_events_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success"=> false,
            "message" => $get_particular_events_message
        ));
        exit;
}
$get_particular_events->bind_param("sss", $owner, $_SESSION['username'], $date);
$get_particular_events->execute();
$get_particular_events_result= $get_particular_events->get_result();
$particular_events_array = array();
$i =0;
while($row = $get_particular_events_result->fetch_assoc()){
    $particular_events_array[$i] = $row;
    $i++;
}
// pass an array of events to javascript
$get_particular_events->close();

echo json_encode(array(
    "success"=>true,
    "message" => "Successfully get the particular events",
    "particular_events_array" => $particular_events_array
));



?>