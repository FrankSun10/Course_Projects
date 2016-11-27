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

$username = htmlentities($_POST['username']);
$password = htmlentities($_POST['password']);

// check empty info
if(empty($username) || empty($password)){
    echo json_encode(array(
       "success" => false,
       "message" => "Please input username and password"
    ));
    exit;
}

$user_login = $mysqli->prepare("select count(*), password from users where username = ?");
if(!$user_login){
      $login_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success"=> false,
            "message" => $login_message
        ));
        exit;
}

$user_login->bind_param('s',$username);
$user_login->execute();
$user_login->bind_result($count_result, $crypted_password);
$user_login->fetch();
$user_login->close();
if($count_result == 1 && crypt($password, $crypted_password) == $crypted_password){ // check valid user info
    $_SESSION['username'] = $username;
    $_SESSION['token'] = substr(md5(rand()), 0, 10);
    echo json_encode(array(
       "success" => true,
       "token" => $_SESSION['token'],
       "username" => $_SESSION['username'],
       "message" => "Succefully logedin"
    ));
}
else{
    echo json_encode(array(
       "success" => false,
       "message" => "Username does not exist or wrong password"
    ));
    exit;
}


?>