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
?>

<!DOCTYPE html>
<html>
    <head>
        <title>Calendar</title>
        <link href="http://ajax.googleapis.com/ajax/libs/jqueryui/1.7.2/themes/start/jquery-ui.css" type="text/css" rel="Stylesheet" />
        <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.3/jquery.min.js"></script>
        <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.5/jquery-ui.min.js"></script>
        <script type="text/javascript" src="http://classes.engineering.wustl.edu/cse330/content/calendar.js"></script>
        <link rel="stylesheet"  type="text/css" href="style-sheet.css">

    </head>
    <body>

        <!-- add an input tag for toke verification and username -->

        <input type="hidden" class= "record" id="token" value="<?php echo $_SESSION['token'];?>" /> <!-- record the token value-->
        <input type="hidden" class= "record" id="login-check" value="false" /> <!-- check if loged in, if  so display the events when click the prevmonth and nextmonth button-->
        <input type="hidden" class= "record" id="username" value="" />  <!-- record the username-->
        <input type="hidden" class= "record" id="is-viewing-shared" value="false" /> <!-- record if is viewing the shared calendar, if so all nextmonth and prevmonth button to handle-->

        <!-- start the header part, simple navbar-->
        <nav id="header" class="header">
            <div id="hello-user"><!--append the welcome message text later on-->   
            </div>

            <div id="page-title">PERSONAL EVENT CALENDAR</div>
            
            <div id= "header-button">
                <input type="button" class="header-button" id="login" value="Login"/>
                <input type="button" class="header-button" id="sign-up" value="Sign up" />
                <input type="button" class="header-button" id="logout" value="Logout" /> <!--show logout button after login-->
            </div>
        </nav>
        <!--end of the navbar-->
        
        <!--forms for registering-->
        <div id="register-form" title="Register" class="dia-forms">
            Username: <br> <input type="text" name="regi-username" id="regi-username"/> <br>
            Password: <br> <input type="password" name="regi-password" id="regi-password"/> <br>
            Confirm password: <br> <input type="password" name="password-confirm" id="password-confirm" /> <br>
            <br> <br>
            <input type="button" id="register-button" value="Register" />
            <!-- end of registering form-->
        </div>
        <!--end of registering form-->
    
        <!--form for login-->
        <div id="login-form" title="Login" class="dia-forms">
            Username: <br> <input type="text" name="login-username" id="login-username" /> <br>
            Password:<br> <input type="password" name="login-password" id="login-password" /> <br>
            <br> <br>
            <input type="button" id="login-button" value="Login" />
        </div>
        <!--end of login form-->
        
        <!--form for creating new user group-->
        <div id='new-user-group-form' title='New Group' class='dia-forms'>
            Group Name: <input type='text' id='new-group-name'/><br>
            Add Users: <br>
            <ul id='new-group-form-user-list'>
                <!--Display added users here-->
            </ul>
            <input type='text' id='new-group-username'/> <input type="button" id="add-group-user-button" value="Add"/><br>
            <input type="button" id='create-new-group-button' value="Create new group"/>
        </div>
        
        <!--div for today's info and month info-->
        <div id="time-nav">
            <div id="today-box"><!--display today's info--></div>
            <br>
            <div id="month-box">
                <input id="previous-month-button"  class= "month-box" type="button" value="<<" /> 
                <div id="month-info" class="month-box"><!--display month info--> </div>
                <input id="next-month-button" class="month-box" type="button" value=">>" />
            </div>
            <br>
            <input id="go-back-to-today-button" type="button" value="Go-Back-To-Today" />
            
            <!-- display buttton for creative part, To-Share, Shared-From, .......-->
            <div id="share-and-group-nav" >
                <div id="others-shared" class="share-link">
                    <a href="#!" >Calendars Shared By Others</a>
                </div>
                <div id="go-back-to-my-calendar" class="share-link">
                    <a href="#!" >Go Back To My Calendar</a>
                </div>
            </div>
            <!-- end of button for creative part -->
            
            <!--section for groups-->
            <div id="user-groups-nav">
                <p style="color:white; font-size: 1.2em;">Groups:</p>
                
                <!--display user groups here-->
                <ul id="user-group-list">
                </ul>
                            
                <br><input id="add-user-group-button" type="button" value="Add New Group" />
            </div>
            
        </div>

        <!--end of today's info and month info-->
        

        
        <!--display the week days from sunday to monday-->
        <div id="calendar-block">
            <table id="calendar-table">
                <thead id="calendar-head">
                    <tr id="weekdays">
                        <th class="weekdays-name" id="head-Sunday">Sunday</th>
                        <th class="weekdays-name" id ="head-Monday">Monday</th>
                        <th class="weekdays-name" id="head-Tuesday">Tuesday</th>
                        <th class="weekdays-name" id="head-Wednesday">Wednesday</th>
                        <th class="weekdays-name" id="head-Tursday">Thursday</th>
                        <th class="weekdays-name" id="head-Friday">Friday</th>
                        <th class="weekdays-name" id="head-Saturday">Saturday</th>
                    </tr>
                </thead>
                <tbody id="calendar-body">
                    <!--first append a row that will have 7 ths, inside each cell append the date info and events in tag a-->
                    <!-- for each row, give it class attribute as class="calendar-body-row"-->
                    <!-- for each cell, give it class attritute as class="calendar-body-cell"-->
                </tbody>
            </table>
            
        </div>
        
        <!--event edit and delete form-->
        <div id="event-edit-delete-form" class="dia-forms" title="">
            Content: <br><br>
            <input id="event-edit-content" value="" /><br><br>
            Category: <br><br>
            <!-- add category radio buttons for events. creative part-->
            <div class="category-block">      
                <input id="edit-category-urgent" type="radio" name="edit-category" value="urgent"/>Urgent<br>
                <input id="edit-category-important" type="radio" name="edit-category" value="important"/>Important<br>
                <input id="edit-category-normal" type="radio" name="edit-category" value="normal" />Normal<br>
                <br> <br>  
            </div>
            <!--end of category radio button-->
            <input id="event-edit-save-button" type="button" value="Save"/>
            <input id="event-delete-button" type="button" value="Delete" />
            <!-- add share button that allows user to share the particular event to other users-->
            <input id="share-button" type="button" value="Share" />
            <!--add remove button that is used to remove shared events-->
            <input id="remove-button" type="button" value="Remove" />
        </div>
        <!--end of edit and delete form-->
        
        <!-- add event form-->
        <div id="add-event-form" class="dia-forms" title="Add event">
            Content: <br> 
            <input id="add-event-content" type="text" /><br><br>
            <!-- add category radio buttons for events. creative part-->
            <div class="category-block">      
                <input id="add-category-urgent" type="radio" name="add-category" value="urgent"/>Urgent<br>
                <input id="add-category-important" type="radio" name="add-category" value="important"/>Important<br>
                <input id="add-category-normal" type="radio" name="add-category" value="normal" />Normal<br>
                <br> <br>  
            </div>
            <!--end of category radio button-->
            <input id="add-event-save-button" type="button" value="Save"/>
        </div>
        <!--end of add event form-->
        
        <!--add users' name sheet, creative part-->
        <div id="users-name-dialog" class="dia-forms" title="Choose-Users">
            <div id="users-name-sheet">
            <!-- append users' names as check boxes, which are going to be quired from the databases-->
            </div>
            <input type="button" id="share-ok-button" value="OK" />
        </div>
        <!-- end of user's name sheet-->
        
        <!-- add owners' name sheet, creative part-->
        <div id="owners-name-dialog" class="dia-forms" title="Choose-Users">
            <div id="owners-name-sheet">
                <!-- append owners name, and radio box-->
            </div>
            <input type="button" id="share-view-button" value="View" />
        </div>
        
        
        
        <script type="text/javascript" src="functions.js"></script>
        <script type="text/javascript" src="user_groups.js"></script>
    </body>
</html>
    