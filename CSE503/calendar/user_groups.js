//show the form for creating a new group
$("#add-user-group-button").click(function(){
    $("#new-user-group-form").dialog();
});

///////////////////////////////////////////////////////////////////////////////////////////////////
//Functions for the add/edit group form

//when the add button is clicked, check if user exists. If yes add the user to the list.
//If no, alert the user
$("#add-group-user-button").click(function(){
    var new_group_username = $("#new-group-username").val();
    var check_user_request = new XMLHttpRequest();
    var token = document.getElementById("token").value; // get the session token value
    var dataString = "token=" + encodeURIComponent(token) + "&new-group-username="+new_group_username;
    check_user_request.open("POST", "check_user_exists.php", true);
    check_user_request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    check_user_request.addEventListener("load", function(event){
        var response = JSON.parse(event.target.responseText);
        if (response.success) {
            var user_list_item = document.createElement("li");
            user_list_item.textContent = new_group_username;
            user_list_item.id = new_group_username;
            user_list_item.className = "added-group-user";
            document.getElementById("new-group-form-user-list").appendChild(user_list_item);
        }
        else{
            alert(response.message);
        }
    }, false);
    check_user_request.send(dataString);
});

//create new group button
$("#create-new-group-button").click(function(){
    //prepare data string
    var new_group_name = document.getElementById("new-group-name").value;
    var token = document.getElementById("token").value; // get the session token value
    var dataString = "token=" + encodeURIComponent(token) + "&name="+new_group_name;
    var user_lis = document.getElementsByClassName("added-group-user");
    for (var i=0; i<user_lis.length; i++){
        dataString += "&user"+i+"="+user_lis[i].id;
    }
    
    //prepare request
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST", "add_user_group.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        //if success, display the newly added user group in the window
        var response = JSON.parse(event.target.responseText);
        if (response.success) {
            var user_group_list = document.getElementById("user-group-list");
            new_li = document.createElement("li");
            new_li.className = "user-group-li";
            new_li.textContent = response.groupName;
            user_group_list.appendChild(new_li);
        }
        //otherwise note problems in log
        else{
            console.log("Error: "+response.message);
        }
    });
    xmlHttp.send(dataString);
});

///////////////////////////////////////////////////////////////////////////////////////////////////

