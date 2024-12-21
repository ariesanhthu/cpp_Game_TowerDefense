//#include "UserManager.h"
//
//std::shared_ptr<UserManager> UserManager::instance = nullptr;
//
//void UserManager::GET_ALL_USER() {
//    // Read all users from file and populate the users vector
//    std::ifstream file("Storage/users.catfam", std::ios::binary);
//    if (file.is_open()) {
//        while (file.peek() != EOF) { // Ensure we don't read past the end of the file
//            std::shared_ptr<User> user = std::make_shared<User>();
//            size_t nameLength, passwordLength;
//
//            // Read lengths of the strings first
//            file.read((char*)&nameLength, sizeof(size_t));
//            file.read((char*)&passwordLength, sizeof(size_t));
//
//            // Read name and password
//            std::string name(nameLength, '\0');
//            std::string password(passwordLength, '\0');
//            file.read(&name[0], nameLength);
//            file.read(&password[0], passwordLength);
//
//            user->setName(name);
//            user->setPassword(password);
//
//            users.push_back(user);
//        }
//        file.close();
//    }
//}
//
//void UserManager::POST_ALL_USER() {
//    // Write all users from the users vector to file
//    std::ofstream file("Storage/users.catfam", std::ios::binary | std::ios::trunc);
//    if (file.is_open()) {
//        for (const auto& user : users) {
//            std::string name = user->getName();
//            std::string password = user->getPassword();
//            size_t nameLength = name.size();
//            size_t passwordLength = password.size();
//
//            // Write lengths of the strings first
//            file.write((char*)&nameLength, sizeof(size_t));
//            file.write((char*)&passwordLength, sizeof(size_t));
//
//            // Write name and password
//            file.write(name.c_str(), nameLength);
//            file.write(password.c_str(), passwordLength);
//        }
//        file.close();
//    }
//}
//
//void UserManager::POST_NEW_USER(std::shared_ptr<User> user) {
//    // Add new user to users vector and write to file
//    users.push_back(user);
//    POST_ALL_USER();
//}
//
//void UserManager::DELETE_USER(std::string name) {
//    // Remove user from users vector and write to file
//    for (size_t i = 0; i < users.size(); ++i) {
//        if (users[i]->getName() == name) {
//            users.erase(users.begin() + i);
//            break;
//        }
//    }
//    POST_ALL_USER();
//}
//
//UserManager::~UserManager() {
//    users.clear();
//}
//
//UserManager::UserManager() : token(nullptr) {
//    GET_ALL_USER();
//}
//
//void UserManager::saveUserToken(std::shared_ptr<User> user) {
//    token = user;
//}
//
//std::shared_ptr<User> UserManager::getUserToken() {
//    return token;
//}
//
//void UserManager::destroyUserToken() {
//    token = nullptr;
//}
//
//bool UserManager::login(string username, string password) {
//    for (const auto& user : users) {
//        if (user->getName() == username && user->getPassword() == password) {
//            saveUserToken(user);
//            return true;
//        }
//    }
//    return false;
//}
//
//bool UserManager::logout() {
//    if (token != nullptr) {
//        destroyUserToken();
//        return true;
//    }
//    return false;
//}
//
//bool UserManager::registerUser(string username, string password) {
//    for (const auto& user : users) {
//        if (user->getName() == username) {
//            return false;
//        }
//    }
//    std::shared_ptr<User> user = std::make_shared<User>(username, password);
//    POST_NEW_USER(user);
//    return true;
//}
//
//std::vector<std::shared_ptr<User>> UserManager::getUserList() {
//    return users;
//}
//
//void UserManager::printListUserForTest() {
//    std::cout << "User List:" << std::endl;
//    for (const auto& user : users) {
//        std::cout << "Name: " << user->getName() << ", Password: " << user->getPassword() << std::endl;
//    }
//}
