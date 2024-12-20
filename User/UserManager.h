#pragma once

#include "User.h"
#include <vector>
#include <memory>
#include <fstream>


class UserManager {
private:
	std::vector<std::shared_ptr<User>> users;
	std::shared_ptr<User> token;

public:
	UserManager();
	~UserManager();

	bool login(string username, string password);
	bool logout();
	bool registerUser(string username, string password);

	void saveUserToken(std::shared_ptr<User> user);
	std::shared_ptr<User> getUserToken();
	void destroyUserToken();

	void POST_ALL_USER();
	void POST_NEW_USER(std::shared_ptr<User> user);
	void GET_ALL_USER();
	void DELETE_USER(string name);

	std::vector<std::shared_ptr<User>> getUserList();

	void printListUserForTest();
};

