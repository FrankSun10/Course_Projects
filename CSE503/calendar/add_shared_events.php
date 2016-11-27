<?php
//validate web security
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

$event_id = htmlentities($_POST['event_id']);
$array_users = json_decode($_POST['shared_to']); // retrive the array
$owner = $_SESSION['username'];

//get the event info from events table
$get_event = $mysqli->prepare("select * from events where id = ?");
if(!$get_event){
        $get_event_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success"=> false,
            "message" => $get_event_message
        ));
        exit;
}
$get_event->bind_param("s", $event_id);
$get_event->execute();
$get_event_result= $get_event->get_result()->fetch_assoc();
$get_event->close();

// update the sharedevents table
for( $i = 0; $i < count($array_users); $i++){
    
    //get the event info from events table
    $insert_shared = $mysqli->prepare("insert into sharedevents (owner, sharedto, content, date, category) values (?,?,?,?,?)");
    if(!$insert_shared){
            $insert_event_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
            echo json_encode(array(
                "success"=> false,
                "message" => $insert_event_message
            ));
            exit;
    }
    $insert_shared->bind_param("sssss", $get_event_result['owner'], $array_users[$i], $get_event_result['content'], $get_event_result['date'], $get_event_result['category'] );
    $insert_shared->execute();
    $insert_shared->close();
    
}

echo json_encode(array(
   "success"=>true,
   "message" => "Successfully shared"
));
?>