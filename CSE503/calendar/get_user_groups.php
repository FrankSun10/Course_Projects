<?php
require("database.php");
session_start();

//get groups from the database
$sql = "select name from groups2users join groups on (groups2users.group_id= groups.id) where username='".$_SESSION['username']."';";
$query = $mysqli->prepare($sql);
if ($query){
    $groups = array();
    $query->execute();
    $query->bind_result($name);
    while($query->fetch()){
        array_push($groups, $name);
    }
    echo json_encode(array(
        "success" => true,
        "groups" => $groups
    ));
}
else{
    echo json_encode(array(
        "success" => false,
        "message" => $mysqli->error
    ));
}
?>