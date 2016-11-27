<?php
header("Content-Type: application/json");// set the MIME type to application/jason to send a json response
require "database.php";
$username = htmlentities($_POST['username']);
$password = htmlentities($_POST['password']);
$password_confirm = htmlentities($_POST['password-confirm']);

if(!empty($username) && !empty($password) && $password === $password_confirm){
    // check if user already exist
    $user_validate = $mysqli->prepare("select count(*) from users where username= ?");
    if(!$user_validate){
        $register_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success"=> false,
            "message" => $register_message
        ));
        exit;
    }
    $user_validate->bind_param('s', $username);
    $user_validate->execute();
    $user_validate->bind_result($count_result);
    $user_validate->fetch();
    $user_validate->close();
    if($count_result != 0){
        echo json_encode(array(
            "success"=>false,
            "message"=>"Username already exists"
        ));
        exit;
    }
    // if the username is valid then insert the user info into the database
    //encrypt password
    $cypted_password = crypt($password);
    $user_insert = $mysqli->prepare("insert into users (username, password) values (?, ?)");
    if(!$user_insert){
        $register_message = sprintf("Query prepare failed: %s\n",$mysqli->error);
        echo json_encode(array(
            "success" => false,
            "message" => $register_message
        ));
        exit;
    }
    $user_insert->bind_param('ss', $username, $cypted_password);
    $user_insert->execute();
    $user_insert->close();
    echo json_encode(array(
        "success" => true,
        "message" => "Successfully registered"
    ));
}
else{ // the input is not completed
    echo json_encode(array(
        "success" => false,
        "message" => "Failed registering"
    ));
    exit;
}
?>