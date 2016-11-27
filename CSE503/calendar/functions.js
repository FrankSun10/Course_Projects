// this script includes functions that would be used in the calendar.php

//////////////////////////////////////////////////////////////////////block of all event listeners

// add event listener for the sign up button, pop up a form for registering
document.getElementById("sign-up").addEventListener("click", function(event){
    $("#register-form").dialog();
}, false);

// add event listerner for the register button, call function register, the button is in the dialog of register form
document.getElementById("register-button").addEventListener("click", register, false);
    
// add eventlistener for login button
document.getElementById("login").addEventListener("click",function(event){
    $("#login-form").dialog();
}, false);

// add eventlistener for the login-button, this button is in the dialog of login form
document.getElementById("login-button").addEventListener("click",login,false);

// add functions and eventlistener for the logout-button
document.getElementById("logout").addEventListener("click", logout, false);

// display today and current month info as soon as the page is loaded
document.addEventListener("DOMContentLoaded",getTimeNav, false);

// show the calendar when the page is loaded
document.addEventListener("DOMContentLoaded", function(){updateCanlendar(current_month_obj);},false);

// event listener for event delete button
document.getElementById("event-delete-button").addEventListener("click", function(){
    delete_event();
    $("#event-edit-delete-form").dialog('close');
    updateCanlendar(current_month_obj);
    get_events_monthly(current_month_obj);   
    },false);

// event listener for event edit save button
document.getElementById("event-edit-save-button").addEventListener("click", function(){
    save_edited_event();
    $("#event-edit-delete-form").dialog('close');
    updateCanlendar(current_month_obj);
    get_events_monthly(current_month_obj);
    },false);

// event listener for add-event-save button
document.getElementById("add-event-save-button").addEventListener("click", function(){
    add_event();
    $("#add-event-form").dialog('close');
    updateCanlendar(current_month_obj);
    get_events_monthly(current_month_obj);
    document.getElementById("add-event-content").value = "";
    
    },false);

// event listener for previous button
document.getElementById("previous-month-button").addEventListener("click", function(){
    current_month_obj = current_month_obj.prevMonth(); // get previous month object
    updateCanlendar(current_month_obj);
    if (document.getElementById("login-check").value == "true") {
        if (document.getElementById("is-viewing-shared").value == "true") {
            get_shared_events_monthly(current_month_obj);
        }
        else{
            get_events_monthly(current_month_obj);  
        }
    }
    document.getElementById("month-info").textContent = month_name[current_month_obj.month] + ", " + current_month_obj.year; 
}, false);

//event listener for next month button
document.getElementById("next-month-button").addEventListener("click", function(){
    current_month_obj = current_month_obj.nextMonth(); // get previous month object
    updateCanlendar(current_month_obj);
    if (document.getElementById("login-check").value == "true") {
        if (document.getElementById("is-viewing-shared").value == "true") {
            get_shared_events_monthly(current_month_obj);
        }
        else{
            get_events_monthly(current_month_obj);  
        }
    }
    document.getElementById("month-info").textContent = month_name[current_month_obj.month] + ", " + current_month_obj.year; 
}, false);

//event listener for go-back-to-today button
document.getElementById("go-back-to-today-button").addEventListener("click", function(){
    var today = new Date();
    current_month_obj = new Month(today.getFullYear(), today.getMonth());
    updateCanlendar(current_month_obj);
    if (document.getElementById("login-check").value == "true") {
        if (document.getElementById("is-viewing-shared").value == "true") {
            get_shared_events_monthly(current_month_obj);
        }
        else{
            get_events_monthly(current_month_obj);  
        }
    }
    document.getElementById("month-info").textContent = month_name[current_month_obj.month] + ", " + current_month_obj.year; 
}, false);

// event listener for category radio buttons
document.getElementById("edit-category-urgent").addEventListener("click", function(event){
    category_record = event.target.value;
    category_changed = true;
}, false);
document.getElementById("edit-category-important").addEventListener("click", function(event){
    category_record = event.target.value;
    category_changed = true;
}, false);
document.getElementById("edit-category-normal").addEventListener("click", function(event){
    category_record = event.target.value;
    category_changed = true;
}, false);
document.getElementById("add-category-urgent").addEventListener("click", function(event){
    category_record = event.target.value;
}, false);
document.getElementById("add-category-important").addEventListener("click", function(event){
    category_record = event.target.value;
}, false);
document.getElementById("add-category-normal").addEventListener("click", function(event){
    category_record = event.target.value;
}, false);

//////////////////////////////////////////////////////////////////////////////////////////////////////////end of event listener block

//////////////////////////////////////////////////////////////////////////////////////////////////////// global variables 

 var category_changed = false;
 var category_record = "normal"; // category recorder used for storing the category for a particualr event
 var day = new Date();
 var current_date = day.getDate();
 if (current_date < 10) {
    current_date = "0" + current_date;
 }
 var current_year = day.getFullYear();
 var current_month_id = day.getMonth(); // getMont() return 0 as January, so we call it month_id
 var current_month_obj = new Month(current_year, current_month_id);
 // define new displayment of month, use 3 characters for each month to allow a formatted id for each day cell
 var month_name = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"];
 // form the current date's date-cell-id
 var current_date_cell_id = "" + current_date + "-" + month_name[current_month_id] + "-" + current_year;
 
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////starts of functions

//function for register
function register(event) {
    var username = document.getElementById("regi-username").value;
    var password = document.getElementById("regi-password").value;
    var passwordConfirm = document.getElementById("password-confirm").value;
    // make the urlencoded string
    var dataString = "username=" + encodeURIComponent(username) + "&password=" + encodeURIComponent(password) +"&password-confirm=" + encodeURIComponent(passwordConfirm);
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST", "register.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            //successfully registerd, empty the registering form
            document.getElementById("regi-username").value = "";
            document.getElementById("regi-password").value = "";
            document.getElementById("password-confirm").value = "";
            alert("Succefully registered");
            $("#register-form").dialog('close');
            $("#sign-up").hide();
        }
        else{
            alert(jsonData.message);
        }
    }, false);
   xmlHttp.send(dataString);
}

    
//function for login
function login(event) {
    var username = document.getElementById("login-username").value;
    var password = document.getElementById("login-password").value;
     //make url-encoded string
    var dataString = "username=" + encodeURIComponent(username) + "&password=" + encodeURIComponent(password);
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST", "login.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            // updates toke for later use
            document.getElementById("token").value = jsonData.token;
            //successfully loged in, empty the login form
            document.getElementById("login-username").value = "";
            document.getElementById("login-password").value = "";
            //alert(jsonData.message);
            $("#login-form").dialog('close'); // close the login form dialog
            // show welcome message and logout button, hide login and signup button
            document.getElementById("hello-user").textContent = "Welcome, " + username + "!";
            document.getElementById("login-check").value = "true"; // update login-check input
            document.getElementById("username").value = username;
            $("#login").hide();
            $("#sign-up").hide();
            $("#logout").show();
            document.getElementById("share-and-group-nav").setAttribute("style", "display:block");
            document.getElementById("user-groups-nav").setAttribute("style", "dislplay:block");

            display_groups();
            get_events_monthly(current_month_obj);
        }
        else{
            alert(jsonData.message);
        }
    }, false);
   xmlHttp.send(dataString);
}

//display the user's groups in the sidebar
function display_groups() {
    var group_list = document.getElementById("user-group-list");
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "get_user_groups.php", true);
    xmlHttp.addEventListener("load", function(event){
        var response = JSON.parse(event.target.responseText);
        if (response.success) {
            var group_names = response.groups;
            for (var i=0; i<group_names.length; i++){
                var new_li = document.createElement("li");
                new_li.className = "user-group-li";
                new_li.textContent = group_names[i];
                group_list.appendChild(new_li);
            }
        }
        else{
            console.log(response.message);
        }
    });
    xmlHttp.send(null);
}


// logout function
function logout(event){
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST", "logout.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
    var jsonData = JSON.parse(event.target.responseText);
    if (jsonData.success) {
        alert(jsonData.message);
        // set record element to default and update welcome message 
        document.getElementById("hello-user").textContent = "";
        document.getElementById("login-check").value = false;
        document.getElementById("username").value = "";
        document.getElementById("is-viewing-shared").value = false;
        //handle the buttons
        document.getElementById("share-and-group-nav").setAttribute("style", "display:none");
        $("#logout").hide();
        $("#login").show();
        $("#sign-up").show();
        location.reload();
    }
    else{
        alert(jsonData.message);
    }
    }, false);
    xmlHttp.send(null);
}

 // show today and current month info
 function getTimeNav() {
    document.getElementById("today-box").textContent = "Today is: " + current_date + ", " +
                                month_name[current_month_id] + ", " + current_year;
    document.getElementById("month-info").textContent = month_name[current_month_id] + ", " + current_year;
    //var weeks = current_month_obj.getWeeks();
    //var day = weeks[0].getDates();
    //alert(weeks.length);
 }

// updateCalendar method without events
function updateCanlendar(current_month_obj) {
    $("#calendar-body").empty(); //  empty all child nodes in the calendar body
    var weeks = current_month_obj.getWeeks();
    for(var i=0; i<weeks.length; i++){
      var w = weeks[i];
    //alert(w);
        // first append each week as a row to the calendar body
        var calendar_body = document.getElementById("calendar-body");
        var week_row = document.createElement("tr");
        var week_row_id = "week_row" + i;
        week_row.setAttribute("class", "week_row");
        week_row.setAttribute("id", week_row_id);
        calendar_body.appendChild(week_row);
        // append 7 td children to each row
        var days = w.getDates();
        for(var j=0; j<days.length; j++){
          	var d = days[j];
            var parent_week_row = document.getElementById(week_row_id);
            var date_cell = document.createElement("td");
            // trying to set a unique id for every day cell
            var particular_date = d;
            var id_year = particular_date.getFullYear();
            var id_month = month_name[particular_date.getMonth()];
            var id_date = particular_date.getDate();
            if (id_date < 10) {
                id_date = "0" + id_date;
            }
            var date_cell_id = "" + id_date + "-" + id_month + "-" + id_year;
            date_cell.setAttribute("id", date_cell_id);
            date_cell.setAttribute("class", "day_cell");
            date_cell.setAttribute("overflow", "hidden");
            date_cell.textContent = id_date;
            parent_week_row.appendChild(date_cell);
            // add <br> tag
            var br = document.createElement("br");
            date_cell.appendChild(br);
            // set the day-cells that don't belongs to the current different
            if (id_month != month_name[current_month_obj.month] ) {
                date_cell.setAttribute("style", "background-color: #e0e0d1;");
            }
            //set the current day-cell different
            if (date_cell_id == current_date_cell_id) {
                date_cell.setAttribute("style", "background-color: #ffcccc");
            }
        }
    }
    
}

//handle when event is clicked
function event_clicked(event){                 
    // set the contents in the coming dialog
    var edit_form_title = document.getElementById("event-edit-delete-form");
    edit_form_title.setAttribute("title", event.target.id); // set the title for the dialog
    var edit_event_content = document.getElementById("event-edit-content");
    edit_event_content.value =  event.target.textContent; // display the original content of the event
    //  change the category uncheck
    document.getElementById("edit-category-urgent").checked = false;
    document.getElementById("edit-category-important").checked = false;
    document.getElementById("edit-category-normal").checked = false;
    if (event.target.getAttribute("data-category") == "urgent") {
        document.getElementById("edit-category-urgent").checked = true;
    }
    else if (event.target.getAttribute("data-category") == "important") {
        document.getElementById("edit-category-important").checked = true;
    }
    else {
        document.getElementById("edit-category-normal").checked = true;
    }
    $("#event-edit-delete-form").dialog(); // pops up a dialog
    // deliver the event_id to event-delete button  and event-edit-save button by the name attribute
    document.getElementById("event-delete-button").setAttribute("name", event.target.getAttribute("id"));
    document.getElementById("event-edit-save-button").setAttribute("name", event.target.getAttribute("id") + "-" + event.target.getAttribute("data-category") );
    category_changed = false; // to see whether the category will be changed during eidt
    document.getElementById("share-button").setAttribute("name", event.target.getAttribute("id"));
}

// append every event belongs to a date to the date-cell-id
function append_events_array(date_cell_id, events_array) {
        if (events_array.length == 0) {
            //do nothing
            return false;
        }
        for(var i = 0; i < events_array.length; ++i){// append every events of the date to the date-cell
        var date_cell_parent = document.getElementById(date_cell_id); // get the parent date-cell
        var event_child = document.createElement("a");
        var event_child_id = document.getElementById("is-viewing-shared").value +"-" + date_cell_id + "-" + events_array[i]['id']; // make a unique id for each personal and shared events
        var event_child_category = "" + events_array[i]['category'];
        event_child.textContent = events_array[i]['content'];
        event_child.setAttribute("id", event_child_id);
        event_child.setAttribute("href", "#!event_edit_dialog");  // make sure that "!event_edit_dialog" is id for no tags
        if (event_child_category == "urgent") {
            event_child.setAttribute("style", "color:red");
            event_child.setAttribute("data-category", "urgent");
        }
        else if (event_child_category == "important") {
            event_child.setAttribute("style", "color:#cc00cc");
            event_child.setAttribute("data-category", "important");
        }
        else{
            event_child.setAttribute("style", "color:#2eb82e");
            event_child.setAttribute("data-category", "normal");
        }
        date_cell_parent.appendChild(event_child);
        // add <br> tag
        var br = document.createElement("br");
        date_cell_parent.appendChild(br);
        // event listener, pops a dialog if the event is clicked
        document.getElementById(event_child_id).addEventListener("click",function f(event){                 
            // set the contents in the coming dialog
            var edit_form_title = document.getElementById("event-edit-delete-form");
            edit_form_title.setAttribute("title", date_cell_id); // set the title for the dialog
            var edit_event_content = document.getElementById("event-edit-content");
            edit_event_content.value =  event.target.textContent; // display the original content of the event
            //  change the category uncheck
            document.getElementById("edit-category-urgent").checked = false;
            document.getElementById("edit-category-important").checked = false;
            document.getElementById("edit-category-normal").checked = false;
            if (event.target.getAttribute("data-category") == "urgent") {
                document.getElementById("edit-category-urgent").checked = true;
            }
            else if (event.target.getAttribute("data-category") == "important") {
                document.getElementById("edit-category-important").checked = true;
            }
            else {
                document.getElementById("edit-category-normal").checked = true;
            }
            $("#event-edit-delete-form").dialog(); // pops up a dialog
            $("#remove-button").hide(); // hide the remove button by default
            if (document.getElementById("is-viewing-shared"). value == "true") { // if is viewing shared events, users can remove the shared one
                $("#remove-button").show();
            }
            // deliver the event_id to event-delete button  and event-edit-save button by the name attribute
            document.getElementById("event-delete-button").setAttribute("name", event.target.getAttribute("id"));
            document.getElementById("event-edit-save-button").setAttribute("name", event.target.getAttribute("id") + "-" + event.target.getAttribute("data-category") );
            category_changed = false; // to see whether the category will be changed during eidt
            document.getElementById("share-button").setAttribute("name", event.target.getAttribute("id")); // pass event id to share button
            document.getElementById("remove-button").setAttribute("name", event.target.getAttribute("id")); // send event id to remove button, used to remove shared evnets in sharedevents table
        }, false);
        
    }   
}


// define a function that could fetch events on a particular date-cell
function get_events_daily(date_cell_id){
    var token = document.getElementById("token").value; // get the session token value
    var dataString = "token=" + encodeURIComponent(token) + "&date=" + encodeURIComponent(date_cell_id);
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST","get_events.php",true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            // an array for the events in the date cell
            var events_array= jsonData.event_array;
            // fetch each event in the array

            append_events_array(date_cell_id, events_array);
 
        }
        else{
            alert(jsonData.message);
        }
    },false);
    xmlHttp.send(dataString);
}

//handle click on date cell
function date_cell_clicked(event){
    if (event.target == this) {
        // pop up the add event dialog        
        $("#add-event-form").dialog({title: "Add-Event-" + event.target.getAttribute("id")});
        // pass the date to add-event-save button
        document.getElementById("add-event-save-button").setAttribute("name", event.target.getAttribute("id"));
    }
}

//using function of get_events_daily to form a function to get events monthly
function get_events_monthly(current_month_obj) {
    var weeks = current_month_obj.getWeeks();
    for(var i=0; i<weeks.length; i++){
      var w = weeks[i];
        // append 7 td children to each row
        var days = w.getDates();
        for(var j=0; j<days.length; j++){
            var d = days[j];
            var particular_date = d;
            var id_year = particular_date.getFullYear();
            var id_month = month_name[particular_date.getMonth()];
            var id_date = particular_date.getDate();
            if (id_date < 10) {
                id_date = "0" + id_date;
            }
            var date_cell_id = "" + id_date + "-" + id_month + "-" + id_year;
            // add event listener dates that is today or after today to add event by click
            var new_date = new Date(id_year,particular_date.getMonth(), id_date);
            if (day < new_date || new_date.setHours(0,0,0,0) == day.setHours(0,0,0,0)) {
                document.getElementById(date_cell_id).addEventListener("click", date_cell_clicked, false);
            }
            get_events_daily(date_cell_id);
        }
    }
}

// fuction for adding events
function add_event() {
    var category = category_record;
    var date = document.getElementById("add-event-save-button").getAttribute("name");
    var content = document.getElementById("add-event-content").value;
    if (!/\S/.test(content)) { // check if the content is all whitespaces
        return;
    }
    // update the database
    var token = document.getElementById("token").value;
    var dateString = "token=" +  encodeURIComponent(token) + "&date=" + encodeURIComponent(date) +"&content=" + encodeURIComponent(content) +"&category=" + encodeURIComponent(category);
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST","events_add.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            alert(jsonData.message);
        }
        else{
            alert(jsonData.message);
        }
    }, false);
    xmlHttp.send(dateString);
}

// function for editing events
function save_edited_event() {
    var changed_event_content = document.getElementById("event-edit-content").value; // get the content in the event_edit_form
    var event_id = document.getElementById("event-edit-save-button").getAttribute("name");
    // split the event_id to get the id for the event in the database
    var event_id_split = event_id.split("-"); 
    var event_id_in_database = event_id_split[event_id_split.length - 2];
    var event_category = event_id_split[event_id_split.length - 1];
    if (category_changed) { // if the category of the event is changed after the edit-event-form pops up, use the changed category
        event_category = category_record;
    }
    // update the database
    var token = document.getElementById("token").value;
    // get the session token value
    var dateString = "token=" +  encodeURIComponent(token) + "&event_category=" + encodeURIComponent(event_category)  +"&event_id=" + encodeURIComponent(event_id_in_database) +"&event_new_content=" + encodeURIComponent(changed_event_content);  
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST","events_edit.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            alert(jsonData.message);
        }
        else{
            alert(jsonData.message);
        }
    }, false);
    xmlHttp.send(dateString);
}

// function for deleting event
function delete_event() {
    //split the event_id to get the id for event in the database
    var event_id = document.getElementById("event-delete-button").getAttribute("name");
     var event_id_split = event_id.split("-"); 
    var event_id_in_database = event_id_split[event_id_split.length - 1];
    // update the database
    var token = document.getElementById("token").value;
    // get the session token value
    var dateString = "token=" +  encodeURIComponent(token) + "&event_id=" + encodeURIComponent(event_id_in_database);
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST","events_delete.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
               var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            alert(jsonData.message);
        }
        else{
            alert(jsonData.message);
        }
    }, false);
    xmlHttp.send(dateString);
    
}

////////////////////////////////////////////////////////////////////////////////////////// code for share calendar part including the global variables

 var checked_users = [];


// share-button listner, (1) pass the event-id to the OK button, (2) pops -up the users-name-dialog
document.getElementById("share-button").addEventListener("click", function(event){
    // get the event id in database
    var event_id = event.target.getAttribute("name");
    var event_id_split = event_id.split("-"); 
    var event_id_in_database = event_id_split[event_id_split.length - 1];
    //pass the id in database to OK button
    document.getElementById("share-ok-button").setAttribute("name", event_id_in_database);
    get_users();
    $("#users-name-dialog").dialog();
    // remember to close the event-edit-delete-form when the OK button is hit
}, false);

// event listener for the OK button
document.getElementById("share-ok-button").addEventListener("click", function(event){
   add_shared_event();
    $("#users-name-dialog").dialog('close');
    $("#event-edit-delete-form").dialog('close');
    
}, false);

//handle change to user sheet
function user_sheet_changed(event){ 
    if (event.target.checked) {// push every checked box to the array of checked_users
        checked_users.push(event.target.getAttribute("id"));
    }
    else { // the box becomes unchecked, remove from the array
        var index = checked_users.indexOf(event.target.getAttribute("id"));
        if (index > -1) {
            checked_users.splice(index, 1);
        }
    }
}
// event listener to shared by others buttoon
document.getElementById("others-shared").addEventListener("click",function(){
   get_shared_owners();
   $("#owners-name-dialog").dialog();
    
}, false);

//event listners to the view  button
document.getElementById("share-view-button").addEventListener("click",function(){
    $("#owners-name-dialog").dialog('close');
    document.getElementById("is-viewing-shared").value = true;
    updateCanlendar(current_month_obj);
    get_shared_events_monthly(current_month_obj);
    // hide the save , share, and delete button, so that user is not allowed to manipulate the shared events
    $("#event-edit-save-button").hide();
    $("#event-delete-button").hide();
    $("#share-button").hide();
    //change the title of the calendar to show the owner's name
    var owner = document.getElementById("share-view-button").getAttribute("name"); 
    document.getElementById("page-title").textContent = "SHARED FROM " + owner.toUpperCase();
    
},false);

// event listener to go-back-to-my-calendar button
document.getElementById("go-back-to-my-calendar").addEventListener("click",function(){
    document.getElementById("is-viewing-shared").value = false;
    // show personal calendar
    updateCanlendar(current_month_obj);
    get_events_monthly(current_month_obj);
    // show save, share and delete button
    $("#event-edit-save-button").show();
    $("#event-delete-button").show();
    $("#share-button").show();
    // change the page title to default
    document.getElementById("page-title").textContent = "PERSONAL EVENT CALENTAR";
}, false);

//event listener for the remove button
document.getElementById("remove-button").addEventListener("click", function(){
    delete_shared_event();
    $("#event-edit-delete-form").dialog('close');
    updateCanlendar(current_month_obj);
    get_shared_events_monthly(current_month_obj);
}, false);

// function to get users name
function get_users() {
    checked_users.length = 0; // each time we get users, we firstly empty the array
    $("#users-name-sheet").empty(); // empty the sheet****
    
    var token = document.getElementById("token").value;
    // get the session token value
    var dateString = "token=" +  encodeURIComponent(token);
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST","get_users.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            alert(jsonData.message);
            var users_array = jsonData.users_array; // get the users-array
            var users_sheet = document.getElementById("users-name-sheet"); // get the users-name-sheet object
            if (users_array.length == 1) {// condition that no other users around
                users_sheet.textContent = "You are the only user";
                return;
            }
            var users_sheet_ul = document.createElement("ul");
            users_sheet.appendChild(users_sheet_ul); // append ul tag to the sheet
            for(var i = 0; i < users_array.length; ++i){ // append each user's name as a child to the sheet
                var users_sheet_checkbox = document.createElement("input"); // create checkbox
                users_sheet_checkbox.setAttribute("type", "checkbox");
                if (users_array[i].username.toLowerCase() != document.getElementById("username").value.toLowerCase()) {
                    users_sheet_checkbox.setAttribute("id", users_array[i].username); // pass share-username as the id of the checkbox
                    var users_sheet_li = document.createElement("li"); // create li element
                    users_sheet_li.textContent = users_array[i].username;
                    users_sheet_ul.appendChild(users_sheet_li);
                    users_sheet_li.appendChild(users_sheet_checkbox);
                    //add event listener for each checkbox,                
                    users_sheet_checkbox.addEventListener("change", user_sheet_changed, false); 
                }
            }
        }
        else{
            alert(jsonData.message);
        }
    }, false);
    xmlHttp.send(dateString);
}

// add shared events to database
function add_shared_event() {
    if (checked_users.length === 0) {
        alert("Please choose a user to share");
        return;
    }
    var event_id_database = document.getElementById("share-ok-button").getAttribute("name");
    // connect the database to update shared-events table
    var json_users_array = JSON.stringify(checked_users);
    var token = document.getElementById("token").value;
    var dateString = "token=" +  encodeURIComponent(token) + "&event_id=" + encodeURIComponent(event_id_database) + "&shared_to=" +  encodeURIComponent(json_users_array);
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST","add_shared_events.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            alert(jsonData.message);
        }
        else{
            alert(jsonData.message);
        }
    }, false);
    xmlHttp.send(dateString);
}

// function to get all the owners of the shared events
function get_shared_owners(event) {
    $("#owners-name-sheet").empty(); // empty the sheet****
    // connect to the database
    var token = document.getElementById("token").value;
    var dateString = "token=" +  encodeURIComponent(token) + "&owner=" + encodeURIComponent("") + "&date=" + encodeURIComponent(""); // pass the empty owner and date just make the get_shared_events.php usable for get_shared_events  function
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST","get_shared_events.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            //alert(jsonData.message);
            var shared_events = jsonData.shared_events_array; // get the events array
            if (shared_events.length == 0) {
                alert("No shared event");
                return;
            }
            for(var i = 0; i < shared_events.length; ++i){
                // check if the current user got some shared events
                if (shared_events[i]['sharedto'].toLowerCase() == document.getElementById("username").value.toLowerCase()) {
                    var users_sheet = document.getElementById("owners-name-sheet");
                    // check if the owner is already on the sheet
                    if (document.getElementById("shared-" + shared_events[i]['owner']) == null) {
                        // append radio box
                        var shared_owner_box = document.createElement("input");
                        shared_owner_box.setAttribute("type","radio");
                        shared_owner_box.setAttribute("name", "shared-radio-users");
                        var shared_owner_box_id = "shared-" + shared_events[i]['owner'];
                        shared_owner_box.setAttribute("id", shared_owner_box_id);
                        shared_owner_box.setAttribute("value", shared_events[i]['owner']);
                        users_sheet.appendChild(shared_owner_box);
                        
                        // append div to show the context
                        var shared_owner_div = document.createElement("div");
                        shared_owner_div.textContent = shared_events[i]['owner'];
                        shared_owner_div.setAttribute("style", "display:inline");
                        //shared_owner_div.setAttribute("id","shared-owner-div" + shared_events[i]['owner']);
                        users_sheet.appendChild(shared_owner_div);
                        users_sheet.appendChild(document.createElement("br"));
                        users_sheet.appendChild(document.createElement("br"));
                        
                        // add event listener to each check box
                        var shared_owner_radio_box = document.getElementById(shared_owner_box_id);
                        shared_owner_radio_box.checked = false; // set the radio box to false
                        shared_owner_radio_box.addEventListener("click",function(event){
                            document.getElementById("share-view-button").setAttribute("name", event.target.value); // pass the view-button the owner's name
                        }, false);
                    }
                    
                    
                }
            }
            
        }
        else{
            alert(jsonData.message);
        }
    }, false);
    xmlHttp.send(dateString);
}

//get shared events daily from a particular owner
function get_shared_events_daily(date_cell_id){
    
    var token = document.getElementById("token").value; // get the session token value
    var owner = document.getElementById("share-view-button").getAttribute("name"); // get the owner that the shared events belongs to
    var dataString = "token=" + encodeURIComponent(token) +"&owner=" + encodeURIComponent(owner) + "&date=" + encodeURIComponent(date_cell_id);
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST","get_shared_events.php",true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            // an array for the events in the date cell
            var shared_events_array= jsonData.particular_events_array;
            // fetch each event in the array and append it to the date cell
            append_events_array(date_cell_id, shared_events_array);
            
        }
        else{
            alert(jsonData.message);
        }
    },false);
    xmlHttp.send(dataString);
}

//get shared events monthly
function get_shared_events_monthly(current_month_obj) {
    var weeks = current_month_obj.getWeeks();
    for(var w in weeks){
        // append 7 td children to each row
        var days = weeks[w].getDates();
        for(var d in days){
            var particular_date = days[d];
            var id_year = particular_date.getFullYear();
            var id_month = month_name[particular_date.getMonth()];
            var id_date = particular_date.getDate();
            if (id_date < 10) {
                id_date = "0" + id_date;
            }
            var date_cell_id = "" + id_date + "-" + id_month + "-" + id_year;
            // add event listener dates that is today or after today to add event by click
            var d = new Date(id_year,particular_date.getMonth(), id_date);
            get_shared_events_daily(date_cell_id);
        }
    }
}

// function for deleting event
function delete_shared_event() {
    //split the event_id to get the id for event in the database
    var event_id = document.getElementById("remove-button").getAttribute("name");
     var event_id_split = event_id.split("-"); 
    var event_id_in_database = event_id_split[event_id_split.length - 1];
    // update the database
    var token = document.getElementById("token").value;
    // get the session token value
    var dateString = "token=" +  encodeURIComponent(token) + "&event_id=" + encodeURIComponent(event_id_in_database);
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("POST","shared_events_delete.php", true);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.addEventListener("load", function(event){
        var jsonData = JSON.parse(event.target.responseText);
        if (jsonData.success) {
            alert(jsonData.message);
        }
        else{
            alert(jsonData.message);
        }
    }, false);
    xmlHttp.send(dateString);    
}



    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    