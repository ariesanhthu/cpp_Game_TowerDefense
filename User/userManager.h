#pragma once

#include <string>
#include "User/cFile.h"
#include <vector>

namespace towerdefense {
	class User {
	private: 
		int id = 0; 
		std::string name; 
		std::string password;
		std::vector<int> gameId;

	public: 
		bool authenticated = false;

		User() {
			name = "guess";
			password = "guess";
			id = 0;
			gameId = {};
		}
		User(std::string name, std::string password) {
			this->name = name; 
			this->password = password;
		}

		int getId() const {
			return id;
		}
		std::string getName() const {
			return name;
		}
		std::string getPassword() const {
			return password;
		}
		std::vector<int> getListGame() const {
			return gameId;
		}
		void setId(int id) {
			this->id = id;
		}
		void setName(std::string name) {
			this->name = name;
		}
		void setPassword(std::string password) {
			this->password = password;
		}
		void setListGame(std::vector<int> gameId) {
			this->gameId = gameId;
		}

		bool hregister() {
			std::vector<saveUser> fetchUser = getUserList();

			for (auto user : fetchUser) {
				if (name == user.name) {
					return false;
				}
			}

			saveUser s;
		
			s.UserId = 1;
			if (fetchUser.size() == 0) {
				s.UserId = 0;
			}
			else {
				s.UserId = fetchUser[fetchUser.size() - 1].UserId + 1;
			}
			s.name = name;
			s.password = password;
			appendUserToFile(s);

			authenticated = true;
			return true;
		}

		bool hlogin() {
			std::vector<saveUser> fetchUser = getUserList();

			for (auto user : fetchUser) {
				if (name == user.name) {
					if (password == user.password) {
						authenticated = true;
						id = user.UserId;
						return true;
					}
				}
			}

			return false;
		}

		void hlogout() {
			authenticated = false;
		}

		bool isAuthenticated() {
			return authenticated;
		}
	};
}


