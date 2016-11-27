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
$token = htmlentities($_POST['token']);

// verify token value
if($_SESSION['token'] != trim($_POST['token'])){
    echo json_encode(array(
       "success"=>false,
       "message" => "token dismatch",
    ));
    die("Requsest forgery detected");
}

$delete_event = $mysqli->prepare("delete from sharedevents where id = ?");
if(!$delete_event){
        $delete_event_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success"=> false,
            "message" => $delete_event_message
            ));
        exit;
}
$delete_event->bind_param("s", $event_id);
$delete_event->execute();
$delete_event->close();

// success message
echo json_encode(array(
   "success"=>true,
   "message" => "Successfully removed"
));

?>