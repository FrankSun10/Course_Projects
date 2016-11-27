// Require the packages we will use:
var http = require("http"),
	socketio = require("socket.io"),
	url = require('url'),
	path = require('path'),
	mime = require('mime'),
	fs = require('fs');

	
//Create object to store chat rooms
var rooms = {};
//to add a room called 'room1' with users 'user1' and 'user2':
//rooms['room1'] = {'name':'room1', 'users':{'user1', 'user2'}, blacklist:{}};
var users = {};

var app = http.createServer(function(req, resp){
	var filename = path.join(__dirname, "client_static", url.parse(req.url).pathname);
	(fs.exists || path.exists)(filename, function(exists){
		if (exists) {
			fs.readFile(filename, function(err, data){
                if(err) return resp.writeHead(500);
                resp.writeHead(200);
                resp.end(data);
			});
		}else{
			// File does not exist
			resp.writeHead(404, {
				"Content-Type": "text/plain"
			});
			resp.write("Requested file not found: "+filename);
			resp.end();
			return;
		}
	});
});
app.listen(3456);
 
// Do the Socket.IO magic:
var io = socketio.listen(app);
io.sockets.on("connection", function(socket){  // This callback runs when a new Socket.IO connection is established.
	

	
	//send the new client the room list
	io.sockets.emit("create_rooms_to_clients", {"rooms": rooms});
	console.log("New connection");
	
	// handle create username
	socket.on("newuser_to_server", function(data, callback){
		if (data.username in users) {
            callback({"success": false});
        }
		else{
			callback({"success": true, "name":data.username});
			console.log(data.username);
			socket.username = data.username; // tract the username on the server side
			users[data.username] ={
				"socket" : socket
			};
		}
	});
	
	//create a room
	socket.on("create_room_to_server", function(data, callback){
		// check if the room_name already exists
		if (data.room_name in rooms) {
            callback({"success": false});
        }
		else{
			rooms[data.room_name] ={
				"owner" : data.owner,
				"category": data.category,  // add category just trying to make it a creative one
				"password" : data.password,
				"users_in" : [],   // for tracking users in the room later
				"black_list" : [],      // for tracking the blocked users in the room
				"numVotes" : 0  // used for record the number of votes to kick a user
			}
			socket.join(data.room_name); // the creator automatically join the room
			socket.room = data.room_name;
			callback({"success" : true, "room_name":data.room_name, "rooms":rooms});
			// send the new room array to every socket
			io.sockets.emit("create_rooms_to_clients", {"rooms": rooms});
		}
	});
	
	// joining a room
	socket.on("join_room_to_server", function(data){
		// check if user is on the black list
		if (rooms[data.room_name].black_list.indexOf(data.username) != -1) { 
            socket.emit("join_room_to_client", {"success": false}); // only send back message to the socket 
        }
		else{
			socket.join(data.room_name);
			rooms[data.room_name].users_in.push(data.username);
			io.to(data.room_name).emit("join_room_to_clients", {"room_name": data.room_name, "rooms":rooms}); // send back to all sockets
		}	
	});
	
	// sending messages
	socket.on('message_to_server', function(data) {
		var message = data.message;
		var room_name = data.room_name;
		var username = data.username;
		// broadcast to the users in the same room
		io.to(room_name).emit("message_to_clients", {"message":message, "username": username});
	});
	
	//sending private messages
	socket.on('private_message_to_server', function(data){
		var message = data.message;
		var to_user = data.to_user;
		var username = data.username;
		users[to_user].socket.emit("private_message_to_client", {"from_user":username, "message":message});
	});
	
	//leaving a room
	socket.on("leave_room_to_server", function(data){
		var room_name = data.room_name;
		var user_to_leave = data.username;
		if (data.is_owner) {// destroy the room
			socket.leave(room_name); // owner leaves
			// all users should leave the room 
			var users_in_this_room = rooms[room_name].users_in;
			for(var i = 0; i < users_in_this_room.length; ++i){
				users[users_in_this_room[i]].socket.leave(room_name);
				users[users_in_this_room[i]].socket.emit("leave_room_to_clients", {"isDestroyed" : true, "message": "Sorry, the creater has destroyed the room"});
			}
			// delete the room
			delete rooms[room_name];
			io.sockets.emit("room_destroyed_to_clients", {"rooms" : rooms});
        }
		else{
			socket.leave(room_name);
			rooms[room_name].users_in.splice(rooms[room_name].users_in.indexOf(user_to_leave), 1);
			io.to(room_name).emit("leave_room_to_clients", {"isDestroyed": false, "room_name" : room_name, "rooms": rooms}); // sending back to update userlist
		}
		
	});
	
	// kick user
	socket.on("kick_user_to_server", function(data){
		
		if (rooms[data.room_name].users_in.indexOf(data.user_to_be_kicked) == (-1)) { //  no such user exits in this room
            socket.emit("kick_user_to_prompter", {"success":false, "message" : "user is not in the room" });
        }
		else{
			
			rooms[data.room_name].numVotes = 1; // record the creator 
			var users_in_the_room = rooms[data.room_name].users_in;
			var numUsers = users_in_the_room.length;
			//if the owner and the kicked user are the only ones in the room, kick the user
			if (numUsers==1) {
				users[data.user_to_be_kicked].socket.leave(data.room_name); // leave the room
				rooms[data.room_name].users_in.splice(rooms[data.room_name].users_in.indexOf(data.user_to_be_kicked), 1); // remove from user list
				users[data.user_to_be_kicked].socket.emit("vote_result_to_client", {"success": true, "isTheOne" : true, "message": "You have been kicked out the room"})
				socket.emit("vote_result_to_client", {"success" : true, "isTheOne" :false, "rooms" : rooms, "message" : "The user has been kicked out"});
			}
			else{
				//otherwise put it to a vote
				socket.emit("kick_user_to_prompter", {"success":true, "message" : "user is not in the room" });
				for(var i = 0; i < numUsers; ++i){
					if (users_in_the_room[i] != data.user_to_be_kicked) { // send the promotion to every user except the one to be kicked
					   users[users_in_the_room[i]].socket.emit("kick_user_to_client", { "user_to_be_kicked" : data.user_to_be_kicked ,"vote": "vote for kicking out user: " + data.user_to_be_kicked});
					}
				}
			}
		}	
	});
	// kick user vote
	socket.on("vote_result_to_server", function(data){
		rooms[data.room_name].numVotes += 1;
		var users_in_the_room = rooms[data.room_name].users_in;
		var numUsers = users_in_the_room.length;
		if (rooms[data.room_name].numVotes >= (numUsers - 1) / 2) {
			users[data.user_to_be_kicked].socket.leave(data.room_name); // leave the room
			rooms[data.room_name].users_in.splice(rooms[data.room_name].users_in.indexOf(data.user_to_be_kicked), 1); // remove from user list
			users[data.user_to_be_kicked].socket.emit("vote_result_to_client", {"success": true, "isTheOne" : true, "message": "You have been kicked out the room"})
			users[data.room_owner].socket.emit("vote_result_to_client", {"success" : true, "isTheOne" :false, "rooms" : rooms, "message" : "The user has been kicked out"});
            numUsers = numUsers - 1;
			for(var i = 0; i < numUsers; ++i){
				users[users_in_the_room[i]].socket.emit("vote_result_to_client", {"success" : true, "isTheOne": false, "rooms": rooms, "message": "The user has been kicked out"});
				rooms[data.room_name].numVotes -= 1; // make sure only kick the user once
			}
        }
		else{
			return; // only when kicking successed, the user will be notified
		}
	});
	
	//ban user
	socket.on("ban_user_to_server", function(data){
		console.log(rooms);
		debugger;
		if (rooms[data.room_name].users_in.indexOf(data.ban_username) == (-1)) {
			socket.emit("ban_user_to_owner", {
				"success":false,
				"message":"Could not find user "+data.ban_username+" in room "+data.room_name
			});
		}
		else{
			//add user to blacklist for the room
			rooms[data.room_name].black_list.push(data.ban_username);
			//notify clients
			socket.emit("ban_user_to_owner", {
				"success":true
			});
			users[data.ban_username].socket.emit("ban_user_to_banned",{
				"ban_username":data.ban_username
			});
		}
	});
	
	
	// handle user disconnects the sever
	socket.on("disconnect", function(data){
		if (!socket.username) { // user just connect without doing anything
            return;
        }
		else{
			delete users[socket.username];
			console.log(socket.username+" disconnected");
			/*
			if (!socket.room) { // user not join or create a room
                return;
            }
			else{
				if (rooms[socket.room].owner == socket.username) {
                    // need a function to destroy the whole room
                }
				else{
					// need a funtion as leveing the room
				}
			}*/
		}
	});
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
});