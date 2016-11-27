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
// connect to database
$get_users = $mysqli->prepare("select username from users");
if(!$get_users){
        $get_users_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success"=> false,
            "message" => $get_users_message
        ));
        exit;
}

$get_users->execute();
$get_users_result= $get_users->get_result();
$users_array = array();
$i =0;
while($row = $get_users_result->fetch_assoc()){
    $users_array[$i] = $row;
    $i++;
}
// pass an array of events to javascript
$get_users->close();

echo json_encode(array(
   "success"=>true,
   "message" => "Successfully get users' info",
   "users_array" => $users_array
));

?>