var Sequelize = require('sequelize');
var express = require('express');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var session = require('express-session');
var morgan = require('morgan');
var fs = require('fs');
var User = require('./models/user');
var rateLimit = require('express-rate-limit');

// invoke an instance of express application.
var app = express();

// set our application port
app.set('port', 80);

// set morgan to log info about our requests for development use.
app.use(morgan('dev'));

// initialize body-parser to parse incoming parameters requests to req.body
app.use(bodyParser.urlencoded({ extended: true }));

// initialize cookie-parser to allow us access the cookies stored in the browser. 
app.use(cookieParser());

// initialize express-session to allow us track the logged-in user across sessions.
app.use(session({
    key: 'user_sid',
    secret: 'bankbenkbinkbonk',
    resave: false,
    saveUninitialized: false,
    cookie: {
        expires: 600000
    }
}));


// This middleware will check if user's cookie is still saved in browser and user is not set, then automatically log the user out.
// This usually happens when you stop your express server after login, your cookie still remains saved in the browser.
app.use((req, res, next) => {
    if (req.cookies.user_sid && !req.session.user) {
        res.clearCookie('user_sid');        
    }
    next();
});


// middleware function to check for logged-in users
var sessionChecker = (req, res, next) => {
    if (req.session.user && req.cookies.user_sid) {
        res.redirect('/');
    } else {
        next();
    }    
};

//template engine
app.set("view engine", "pug");
app.set("views", __dirname + "/views");


// route for Home-Page
app.get('/', (req, res) => {
    if (req.session.user && req.cookies.user_sid) {
		res.render("homepage", {
			authorized: true,
			username: req.session.user.username
		});
    } else {
		res.render("homepage", {
			authorized: false
		});
    }
});


// route for user signup
app.route('/signup')
    .get(sessionChecker, (req, res) => {
		res.render("signup");
    })
    .post((req, res) => {
        User.create({
            username: req.body.username,
            password: req.body.password,
			credits: 0,
			items: JSON.stringify({cat: 0, haiku: 0, helicopter: 0, flag: 0}),
			messages: []
        })
        .then(user => {
            req.session.user = user.dataValues;
            res.redirect('/');
        })
        .catch(error => {
            res.redirect('/signup');
        });
    });


// route for user Login
app.route('/login')
    .get(sessionChecker, (req, res) => {
		res.render("login");
    })
    .post((req, res) => {
        var username = req.body.username,
            password = req.body.password;

        User.findOne({ where: { username: username } }).then(function (user) {
            if (!user) {
                res.redirect('/signup');
            } else if (!user.validPassword(password)) {
                res.redirect('/login');
            } else {
                req.session.user = user.dataValues;
                res.redirect('/');
            }
        });
    }
);

function renderGift(messages, err_msg, res) {
	var html_message;
	if (messages.length == 0) {
		html_message = "No new messages";
	} else {
		var html_message = "<ul style='list-style-type:none;'>";
		for (var message of messages){
			html_message += "<li>" + message + "</li>"
		}
		html_message += "</ul>";
	}
	res.render("gift",{
		error_message: err_msg,
		new_message: html_message
	});
}

app.route('/gift')
    .get((req, res) => {
		if (req.session.user && req.cookies.user_sid) {
			User.findOne({ where: { username: req.session.user.username } }).then(function (user) {
				if (!user) {
					res.redirect('/login');
				} else {
					renderGift(user.dataValues.messages, '', res);
					user.update({messages: []});
				}
			});
		} else {
			res.redirect('/login');
		}
    })
    .post((req, res) => {
		if (req.session.user && req.cookies.user_sid) {
			var from_user = req.session.user.username;
			var to_user = req.body.username;
			var send_credits = parseInt(req.body.credits);
			var send_message = "User " + from_user + " sent you " + req.body.credits + " credits: " + req.body.message;

			if (send_credits <= 0) {
				renderGift(req.session.user.messages, 'You have to send at least 1 credit.', res);
			} else {

				User.findOne({ where: { username: from_user } }).then(function (user) {
					if (!user) {
						renderGift(req.session.user.messages, 'Invalid FROM User', res);
					} else if(user.dataValues.credits < send_credits){
						renderGift(req.session.user.messages, 'You cannot send more credits than you have.', res);
					} else {
						User.findOne({ where: { username: to_user } }).then(function (user_to) {
							if (!user_to) {
								renderGift(req.session.user.messages, 'Invalid User', res);
							} else {
								user_to.increment('credits', { by: send_credits} );
								if (from_user != 'bob'){
									user.decrement('credits', { by: send_credits} );
								}
								user_to.update({'messages': Sequelize.fn('array_append', Sequelize.col('messages'),send_message)});
								req.session.user = user.dataValues;
								res.redirect('/gift');
							}
						});
					}
				});
			}
		} else {
			res.redirect('/login');
		}
    }
);

app.post('/purchase', (req, res) => {
    if (req.session.user && req.cookies.user_sid) {
		User.findByPk(req.session.user.id).then(user => {
			return user;
		}).then(user => {
			var item = req.body.item;
			var db_items = JSON.parse(user.dataValues.items);
			var reply = item;
			var num_creds = parseInt(user.dataValues.credits);
			if (db_items[item] == 1){
				reply = reply + " already purchased.";
			} else {
				var store = {cat: 10, haiku: 50, helicopter: 1000, flag: 2000000000};
				var price = store[item];
				if (num_creds >= price){
					db_items[item] = 1;
					user.update({items: JSON.stringify(db_items)});
					reply = reply + " purchase successful";
					if (user.dataValues.username != 'bob'){
						user.decrement('credits', { by: price} );
						num_creds = num_creds - price;
					}
					req.session.user = user.dataValues;
					req.session.user.credits = num_creds;
				} else{
					reply = reply + " purchase failed: Not enough credits.";
				}
			}
			res.send({success: true, remaining_credits: num_creds, message: reply});
		});
    } else {
		res.send({success: false, remaining_credits: num_creds, message: "User session expired."});
    }
});

function getItem(item) {
	var filename = "inventory/" + item + ".txt";
	return fs.readFileSync(filename).toString();
}

app.get('/inventory', (req, res) => {
    if (req.session.user && req.cookies.user_sid) {
		var items = JSON.parse(req.session.user.items);
		var inventory = {};
		for (var item in items) {
			if (items[item] == 1) {
				inventory[item] = getItem(item);
			}
		}
		res.render("inventory", inventory);
    } else {
        res.redirect('/login');
    }
});

const creditCreationLimiter = rateLimit({
	windowsMs: 5 * 60 * 1000,
	max: 1000
});

app.post('/newcredit', creditCreationLimiter, (req, res) => {
    if (req.session.user && req.cookies.user_sid) {
		User.findByPk(req.session.user.id).then(user => {
			return user.increment('credits');
		}).then(user => {
			req.session.user = user.dataValues;
			res.send({success: true, message: user.dataValues.credits});
		});
    } else {
		res.send({success: false, message: "User session expired."});
    }
});


// route for user's store
app.get('/store', (req, res) => {
    if (req.session.user && req.cookies.user_sid) {
		User.findByPk(req.session.user.id).then(user => {
			return user;
		}).then(user => {
			res.render("store", {
				num_credits: user.dataValues.credits
			});
		});
    } else {
        res.redirect('/login');
    }
});


// route for user logout
app.get('/logout', (req, res) => {
    if (req.session.user && req.cookies.user_sid) {
        res.clearCookie('user_sid');
        res.redirect('/');
    } else {
        res.redirect('/login');
    }
});


// route for handling 404 requests(unavailable routes)
app.use(function (req, res, next) {
  res.status(404).send("Sorry can't find that!")
});


// start the express server
app.listen(app.get('port'), () => {
	console.log(`App started on port ${app.get('port')}`)
});
