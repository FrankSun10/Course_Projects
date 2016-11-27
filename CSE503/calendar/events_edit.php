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

$event_id = htmlentities($_POST['event_id']);
$event_new_content = htmlentities($_POST['event_new_content']);
$token = htmlentities($_POST['token']);
$event_category = htmlentities($_POST['event_category']);

// verify token value
if($_SESSION['token'] != trim($_POST['token'])){
    echo json_encode(array(
       "success"=>false,
       "message" => "token dismatch",
    ));
    die("Requsest forgery detected");
}

// connet the database
$update_event = $mysqli->prepare("update events set content = ?, category= ? where id = ?");
if(!$update_event){
        $update_events_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success"=> false,
            "message" => $update_events_message
        ));
        exit;
}
$update_event->bind_param("sss", $event_new_content, $event_category, $event_id);
$update_event->execute();
$update_event->close();

echo json_encode(array(
   "success"=>true,
   "message" => "Successfully saved"
));






















?>