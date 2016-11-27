

var myControllers = angular.module('myControllers',[
    'ngRoute',
    'controllers'
    ]).
config(['$routeProvider', function($routeProvider){
    $routeProvider
    .when('/register',{
        templateUrl:'register.html',
        controller: 'registerController',
        css: 'style.css'
    })
    .when('/login', {
        templateUrl: 'login.html',
        controller: 'loginController',
        css: 'style.css'
    })
    .when('/home', {
        templateUrl: 'home.html',
        controller: 'homeController',
        css: 'style.css'
    })
    .when('/newCuisine',{
        templateUrl: 'new_cuisine.html',
        controller: 'newCuisineController',
        css: 'style.css'
    })
    .when('/cuisines/:cuisine_id', {
        templateUrl: 'cuisine_detail.html',
        controller: 'cuisineDetailController',
        css:'style.css'
    })
    .otherwise({
        redirectTo: '/home'
    });
}]);


//crsf service 
myControllers.factory('$csrf', function () {
    var cookies = document.cookie.split('; ');
    for (var i=0; i<cookies.length; i++) {
      var cookie = cookies[i].split('=');
      if(cookie[0].indexOf('XSRF-TOKEN') > -1) {
        return cookie[1];
      }
    }
    return 'none';
});