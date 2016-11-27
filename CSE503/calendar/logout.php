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


//clear session variables
session_unset();

//clear session cookies
if (ini_get("session.use_cookies")) {
$params = session_get_cookie_params();
setcookie(session_name(), '', time() - 42000,
    $params["path"], $params["domain"],
    $params["secure"], $params["httponly"]
);
}
// send back message
if(session_destroy()){
    echo json_encode(array(
       "success" => true,
       "message" => "Succefully logged out"
    ));
}
else{
    echo json_encode(array(
        "success" => false,
        "message" => "Logout failed"
    ));
}

?>