#pragma once
#include <string>
class createNewUser
{
public:
	createNewUser();
	~createNewUser();
	std::string encryptDecrypt(std::string pw);
	void newUser(std::string userName, std::string password);
	void readUsers(std::string name);
	std::string decrypted;
	bool userExist;
};

