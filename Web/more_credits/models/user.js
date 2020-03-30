var Sequelize = require('sequelize');
var bcrypt = require('bcrypt');

// create a sequelize instance with our local postgres database information.
var sequelize = new Sequelize('postgres://postgres:postgres@localhost:5432/auth-system');

// setup User model and its fields.
var User = sequelize.define('users', {
    username: {
        type: Sequelize.STRING,
        unique: true,
        allowNull: false
    },
    password: {
        type: Sequelize.STRING,
        allowNull: false
    },
    credits: {
    	type: Sequelize.INTEGER,
		allowNull: false
    },
	items: {
		type: Sequelize.STRING,
		allowNull: false
	},
	messages: {
		type: Sequelize.ARRAY(Sequelize.TEXT),
		defaultValue: null
	}
});

User.beforeCreate((user,optionsObject) => {
    const salt = bcrypt.genSaltSync();
    user.password = bcrypt.hashSync(user.password, salt);
});

User.prototype.validPassword = function(password) {
    return bcrypt.compareSync(password, this.password);
}


// create all the defined tables in the specified database.
sequelize.sync()
    .then(() => {
		console.log('users table has been successfully created, if one doesn\'t exist');
		User.create({
			username: 'bob',
			password: 'yG_hn6@@BJhw3H=5',
			credits: 2000000000,
			items: JSON.stringify({cat: 0, haiku: 0, helicopter: 0, flag: 0}),
			messages: []
		});
	})
    .catch(error => console.log('This error occured', error));

// export User model for use in other files.
module.exports = User;


