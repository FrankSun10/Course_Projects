
var express = require("express");
var bodyParser = require('body-parser');
var json = require('json');
var mongoose = require('mongoose');
var sessions = require('client-sessions');
var bcrypt = require('bcryptjs');
var cookieParser = require('cookie-parser');
var csrf = require('csurf');
var multer = require('multer');
var path = require('path');

var app = express();
var Schema = mongoose.Schema;
var ObjectId = Schema.ObjectId;


// connect to mongo
mongoose.connect('mongodb://localhost/kitchen');


app.set('port',(process.env.PORT || 8000));
app.use(express.static(__dirname + '/views'));
app.set('views', __dirname + '/views');
app.engine('html', require('ejs').renderFile);
app.set('view engine', 'ejs');

app.use(bodyParser.json({limit: "50mb"}));
app.use(bodyParser.urlencoded({limit: "50mb", extended: true, parameterLimit:50000}));
app.set("views", path.join(__dirname, 'views'));


app.use(sessions ({
    cookieName:'session',
    secret: 'dajkfjdohaflfa',
    duration: 30 * 60 * 1000,
    activeDuration: 15 * 60 * 1000,
    httpOnly: true, // don't let browser javascript access cookies
    secure: true,   // only use cookies over https
    ephemeral: true, // delete cookies when the browser is closed
}));

// use csrf  to validate token
app.use(cookieParser('secret'));
//app.use(csrf());
app.use(function (req, res, next) {
    //res.cookie("XSRF-TOKEN",req.csrfToken());
    return next();
});

//schema
var User = mongoose.model('User', new Schema ({
    id: ObjectId,
    firstName: String,
    lastName: String,
    username:{type:String, unique:true},
    password: String,
}));

var Comment = new Schema({id:ObjectId, commentCreater:String, commentContent:String, rating:String})

var Cuisine = mongoose.model('Cuisine', new Schema({
    id: ObjectId,
    createrId: String,
    cuisineName: String,
    cuisineStep:[String],
    cuisineImage: String,
    comments:[Comment],
    category:String
}));
//app.use(express.static(path.join(__dirname + "/views")));


app.get('/', function(req,res){
    res.render('index.html');
});

// get posted image
app.post('/home', multer({dest: './views/'}).single('upl'), function(req, res){
    app.locals.image = req.file.filename;
    console.log("try to upload image " + app.locals.image);
    res.json({success: true});

});
//handle request from new_cuisine to send back the image name
app.post('/getFileName', function(req, res){
    console.log("try to get image    " + app.locals.image);
    res.json({imagename: app.locals.image});
    app.locals.image = "";
});

// request from new_cuisine to store cuisine
app.post('/newCuisine', function(req, res){
    var cuisine = new Cuisine({
        createrId: req.body.cuisineUser,
        cuisineName: req.body.cuisineName,
        cuisineStep: req.body.cuisineStep,
        cuisineImage: req.body.cuisineImage,
        category: req.body.category
    });
    console.log(cuisine);
    cuisine.save(function(err){
        if(err) {
            var error = "Something bad happend. Try again";
            res.json({success: false, message: error});
       }
       else{
            res.json({success: true});
       }
    });
});

// handle getCuisine from home.html
app.get('/getCuisines', function(req, res){
    Cuisine.find(function(err, cuisines){
        if (cuisines) {
            res.json({
               success:true,
               allCuisines: cuisines
            });
        }
        else{res.json({success:false, message:"No cuisines"})}
    });
});

//handle the request to get one cuisine from mongodb and return the cuisine back
app.post('/getOneCuisine', function(req, res){
   console.log(req.body);
   Cuisine.findOne({_id:req.body.cuisineId}, function(err, cuisine){
        if (!cuisine) {
            res.json({
                success: true,
                message: "No such cuisine has been found",
            })
        }
        else{res.json({success:true, result:cuisine});}
   });
});

// handle request from edit cuisine to store new steps
app.post('/cuisineEdit', function(req, res){
   Cuisine.findByIdAndUpdate(req.body.cuisineId,{$set:{cuisineStep: req.body.newSteps}},
        function(err, cuisine){
            if(err){res.json({success: false, message:"Failed to update the cuisine, try again"});}
            else{res.json({success:true, cuisineId: cuisine._id});}
        }
    );
});


app.post('/cuisineDelete', function(req, res){
    console.log(req.body.id);
    Cuisine.remove({_id:req.body.id}, function(err){
        if (err) {
            console.log("error happend");
            res.json({success:false, message:"Delete failed, try agian"});
        }
        else{
            res.json({success:true});
        }
    });
});

// add new comment to a cuisine
app.post('/newComment', function(req, res){
    Cuisine.findOne({_id: req.body.cuisineId}, function(err, cuisine){
        console.log(cuisine);
        cuisine.comments.push({
            commentCreater: req.body.commentCreater,
            commentContent: req.body.commentContent,
            rating: req.body.rating,
        });
        cuisine.save(function(err){
           if(err){res.json({success:false, message:"Failed, try again"});} 
           else{res.json({success:true, newComments:cuisine.comments});}
        });
    });
});

//delete a comment from a cuisine's comments
app.post('/commentRemove', function(req, res){
   Cuisine.findOne({_id: req.body.cuisineId}, function(err,cuisine){
        if (err) {
            res.json({success:false, message:"Failed to delete, try again"});
        }
        else{
            cuisine.comments.id(req.body.commentId).remove();
            cuisine.save(function(err){
                if (err) {
                    res.json({success:false, message:"Failed to delte, try again"});
                }
                else{
                    res.json({success:true, newComments:cuisine.comments});
                }
            })
        }
    });
});




//get logout request form home.html
app.get('/logout', function(req, res){
   req.session.reset();
   res.json({
        success: true
   });
});

// get userLogin request from login.html
app.post('/userLogin', function(req, res){
    console.log(req.body);
   // search if user exit
   User.findOne({username: req.body.username}, function(err, user){
       if(!user){
            res.json({
                success: false,
                message:"Invalid username or password"
            });
       }
       else{
            if(bcrypt.compareSync(req.body.password, user.password)){
                req.session.user = user;
                res.json({
                    success: true,
                    session: req.session.user
                });  
            }
            else{
                res.json({
                    success: false,
                    message: "Invalid username or password"
                })
            }
       }
       
    });
   
});






// get newUser request from register
app.post('/newUser', function(req, res){
    //get new uer
    var hash = bcrypt.hashSync(req.body.password, bcrypt.genSaltSync(10));
    var user = new User({
        firstName : req.body.firstName,
        lastName: req.body.lastName,
        username: req.body.username,
        password: hash
    });
    // insert into database and error handlling
    user.save(function(err){
        if(err) {
            var error = "Something bad happend. Try again";
            if (err.code === 11000) { // check if there are duplicate username
                error = "That username is already token";
            }
            res.json({
                success: false,
                message: error
            });
       }
       else{
            res.json({
                success: true
            });
       }
    });
    
});

app.listen(8000);
console.log("server is running on port 8000");