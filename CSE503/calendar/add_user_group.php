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
require("database.php");

$token = htmlentities($_POST['token']);

// verify token value
if($_SESSION['token'] != trim($_POST['token'])){
    echo json_encode(array(
       "success"=>false,
       "message" => "token mismatch",
    ));
    die("Request forgery detected");
}

//first insert a group with the posted name into the database
$query1 = $mysqli->prepare("insert into groups(name) values(?);");
$group_id;
if($query1){
    $query1->bind_param("s", $_POST['name']);
    $query1->execute();
    $group_id = $mysqli->insert_id;
    $query1->close();
}
else{
    echo json_encode(array(
        "success" => false,
        "message" => $mysqli->error
    ));
    exit;
}


//now insert rows into groups2users with the newly created id and all the posted usernames
$sql = "INSERT INTO groups2users (group_id, username) VALUES (".$group_id.", '".$_POST['user0']."')";
$i=1;
while(isset($_POST['user'.$i])){
    $sql .= ", (".$group_id.", '".$_POST['user'.$i]."')";
    $i++;
}
$sql .= ";";

$query2 = $mysqli->prepare($sql);
if ($query2){
    $query2->execute();
    $query2->close();
    
    //echo the group name back to the script
    echo json_encode(array(
        "success" => true,
        "groupName" => $_POST['name']
    ));
}
else{
    error_log("Attempted query string: ".$sql);
    echo json_encode(array(
        "success" => false,
        "message" => $mysqli->error
    ));
}
?>





