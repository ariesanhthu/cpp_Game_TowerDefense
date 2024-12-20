#include "User.h"

void User::setName(string name) {
	this->name = name;
}
string User::getName() {
	return name;
}
void User::setPassword(string password) {
	this->password = password;
}
string User::getPassword() {
	return password;
}
User::User(string name, string password) {
	this->name = name;
	this->password = password;
}
User::User() {
	this->name = "guess";
	this->password = "";
}
