var controllers = angular.module('controllers',[]);
var currentUser = "";
var stepCounter = 3;

controllers.controller('homeController', ['$scope', '$http', function($scope, $http){
    
    //fetch cuisines from mongodb
    $http.get('/getCuisines').success(function(data){
       $scope.cuisines = data.allCuisines;
    });
    
    // handle nav button
    if (currentUser == "") {
        $("#after-login").hide();
    }
    else{
        $("#after-login").show();
        $("#register-login").hide();
        
    }
    
    // handle logout button
    document.getElementById("logout-button").addEventListener("click", function(){
        $http.get('/logout').success(function(){
            currentUser = "";
            window.location.reload();   
        });
    }, false);
    
    
}]);

controllers.controller('cuisineDetailController', ['$scope', '$routeParams', '$http', function($scope, $routeParams, $http){
    $scope.rating = "1";
    // check if user is logged in, if not redirect the user to the home page
    if (!currentUser) {
        window.location.href = "#/home";
        return;
    }
    
    var cuisineId = {cuisineId: $routeParams.cuisine_id};
    //get the cuisine with the same id as routeParams.cuisine_id
    $http.post('/getOneCuisine', cuisineId).success(function(data){
        if (!data.success) {
            alert(data.message);
            return;
        }
        // set the scope variable and step counter 
        $scope.cuisine = data.result;
        $scope.steps = data.result.cuisineStep;
        $scope.comments = data.result.comments;
        stepCounter = data.result.cuisineStep.length;
        
        // check if the cuisine belongs to the current user
        if (currentUser._id === $scope.cuisine.createrId) {
            console.log(currentUser._id === $scope.cuisine.createrId)
            $scope.isNotCreater = false;
            $("#edit-save-button").show();
            $("#edit-add-step").show();
            $("#edit-delete-button").show();
        }
        else{
            $scope.isNotCreater = true;
        }
    });
    
    // handle save button, to transfer the edited content to server and store in mongodb
    document.getElementById("edit-save-button").addEventListener("click", function(){
        $scope.steps = [];
        for(var i = 1; i <= stepCounter; ++i){
            $scope.steps[i - 1] = document.getElementById("step" + i).value
        }
        // send new steps to server to store
        var editSteps = {cuisineId: $scope.cuisine._id, newSteps: $scope.steps};
        $http.post('/cuisineEdit', editSteps).success(function(data){
            if (! data.success) {
                alert(data.message);
                return;
            }
            // redirect user to the cuisine detailed page
            window.location.href = "#/home";
        });
    });
   
   //handle the delete button, send the request to server and delete the cuisine in mongodb
   document.getElementById("edit-delete-button").addEventListener("click", function(){
        var cuisineToDelete = {id:$scope.cuisine._id};
        $http.post('/cuisineDelete', cuisineToDelete).success(function(data){
            console.log("cuisine to be deleted " + $scope.cuisine._id);
            if (data.success) {
                window.location.href = "#/home";
            }
        })
   }, false);
   
   // handle the comment buttons
   document.getElementById("comment-button").addEventListener("click", function(){
        // check if the input is empty
        if (!$scope.newComment) {
            alert("Please input the comment");
            return;
        }
        // send the comment to server and store the comment to the cuisine in mongodb
        var commentInfo = {cuisineId:$scope.cuisine._id, commentContent: $scope.newComment, commentCreater:currentUser.username, rating: $scope.rating};
        console.log(commentInfo);
        $http.post('/newComment',commentInfo).success(function(data){
            if (! data.success) {
                alert(data.message);
                return;
            }
            $scope.comments = data.newComments;  // trick to display comments 
            $scope.newComment = ""; // empty the comment box
        });
   });
   // comment remove button
   $scope.commentRemove = function(commentId, commentCreater){
        // not allowed to remove comments belongs to others 
        if (commentCreater != currentUser.username) {
            alert("You are only allowed to remove your comments");
            return;
        }
        // pass the cuisine id and comment id to server to remove the comment to the database
        var commentToRemove = {cuisineId: $scope.cuisine._id, commentId:commentId};
        $http.post('/commentRemove',commentToRemove).success(function(data){
            if (!data.success) {
                alert(data.message);
                return;
            }
            $scope.comments = data.newComments;
        });
   }
   
   //handle add new steps
   document.getElementById("edit-add-step").addEventListener("click",function(){
        stepCounter = stepCounter + 1;
        var newStepBox = document.getElementById("new-steps");
        var label = document.createElement("strong");
        label.textContent = "Step" + stepCounter + ":";
        var newStep = document.createElement("input");
        newStep.setAttribute("id", "step" + stepCounter);
        newStep.setAttribute("type", "text");
        newStep.setAttribute("class", "form-control");
        newStep.setAttribute("placeholder", "Enter step " + stepCounter);
        // append
        newStepBox.appendChild(label);
        newStepBox.appendChild(newStep);
        // change the position of add steps button
        $("#edit-add-step").appendTo("#new-steps");
   }, false);
   
   
    
}]);



controllers.controller('newCuisineController', ['$scope','$http', '$csrf', function($scope, $http, $csrf){
    // set the category default to american
    $scope.category = "American";
    //every time  initialize stepcounter to 3
    stepCounter = 3;
    // reset step counter when user click back to home button
    document.getElementById("back-to-home-button").addEventListener("click", function(){
       stepCounter = 3; 
    });
    
    // function used to input image form
 	$(document).ready(function(){
 		// This is the simple bit of jquery to duplicate the hidden field to subfile
 		$('#cuisine-image').change(function(){
			$('#subfile').val($(this).val());
		});
		// This bit of jquery will show the actual file input box
		$('#showHidden').click(function(){
			$('#cuisine-image').css('visibilty','visible');
		});
 	});
    
    //define a array to store steps
    $scope.step = [];
    
    // save button
    document.getElementById('cuisine-save-button').addEventListener("click", function(){
       var title = document.getElementById("cuisine-title").value;
       var im = document.getElementById("cuisine-image").value;
       var step1 = document.getElementById("step1").value;
       var step2 = document.getElementById("step2").value;
       var step3 = document.getElementById("step3").value;
       // check if all necessary info are input
       if (title == "" || im == "" || step1 == "" || step2 == "" || step3 == "") {
            alert("Please input the title, image and at lease 3 steps");
            return;
       } 
       // form the step array
       for(var i = 1; i <= stepCounter; ++i){
        $scope.step[i - 1] = document.getElementById("step" + i).value;
       }
       console.log($scope.step);
       
       // handle images and  send the cuisine to server to store in  mongod
       $http.post('/getFileName', $scope.step).success(function(data){
            // request the image name from server and sign it to a variable
            console.log("fetched image name " + data.imagename);
            $scope.image = data.imagename;
            var cuisine = {cuisineName: title, cuisineImage:$scope.image,
            cuisineUser: currentUser._id, cuisineStep: $scope.step, category:$scope.category };
            // conduct another request
            return $http.post('/newCuisine', cuisine).success(function(response){
                    if (response.success) {
                        window.location.href = "#/home";
                    }
                    else{
                        alert(response.message)
                    }
                });
       });  
    }, false);
    
    // handle add step, when the button is clicked, append a input form
    document.getElementById("add-step").addEventListener("click", function(){
        stepCounter = stepCounter + 1;
        //prepare each element
        var cuisineForm = document.getElementById("cuisine-form");
        var newStep = document.createElement('div');
        newStep.setAttribute("class", "form-group");
        var newStepLabel = document.createElement('label');
        newStepLabel.setAttribute("class", "control-label col-sm-2");
        newStepLabel.setAttribute("for", "step" + stepCounter);
        newStepLabel.textContent = "Step " + stepCounter + ":";
        var newStepCol = document.createElement('div');
        newStepCol.setAttribute("class", "col-sm-10");
        var newStepContent = document.createElement('input');
        newStepContent.setAttribute("id", "step" + stepCounter);
        newStepContent.setAttribute("type", "text");
        newStepContent.setAttribute("class", "form-control");
        newStepContent.setAttribute("placeholder", "Enter step " + stepCounter);
        // append every element
        cuisineForm.appendChild(newStep);
        newStep.appendChild(newStepLabel);
        newStep.appendChild(newStepCol);
        newStepCol.appendChild(newStepContent);
        // change the position of add steps button
        $("#add-step").appendTo("#cuisine-form");
    }, false);
    
}]);

controllers.controller('loginController', ['$scope', '$http', function($scope, $http){

   document.getElementById("login-button").addEventListener("click", function(){
        var username = document.getElementById('username').value;
        var password = document.getElementById("password").value;
        if (username == "" || password == "") {
            console.log("Invalid input");
            alert("Invalid input");
            return;
        }
        console.log($scope.user);
        // send login info to server
        $http.post('/userLogin', $scope.user).success(function(data){
           console.log(data);
           if (!data.success) {
                alert(data.message);
           }
           else{
                currentUser = data.session;
                console.log(currentUser);
                window.location.href = "#/home";
           }
        });
    
    }, false)
   
}]);



controllers.controller('registerController', ['$scope', '$http', function($scope, $http){
    
    document.getElementById("register-button").addEventListener("click", function(){
        // check if all info is filled
        var first = document.getElementById("firstName").value;
        var last = document.getElementById('lastName').value;
        var username = document.getElementById('username').value;
        var password = document.getElementById("password").value;
        if (first == "" || last == "" || username == "" || password == "") {
            console.log("invalid user");
            alert("Invalid input");
            return;
        }
        console.log($scope.user);
        // send info to server
        $http.post('/newUser', $scope.user).success(function(data){
           if (!data.success) {
                alert(data.message);
           }
           else{
            window.location.href = "#/login";
           }
        });

    },false);

}]);