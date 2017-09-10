#include "createNewUser.h"
#pragma warning(disable : 4996);
#include <fstream>
#include <cstdio>
#include <string>
#include <Windows.h>

createNewUser::createNewUser()
{
}

void createNewUser::readUsers(std::string name) {
	userExist = true;
	std::string password;
	std::string location = "C:/UserAccount/" + name + ".txt";
	std::ifstream findUser(location);

	if (findUser.is_open()) {
		getline(findUser, password);
	}
	else {
		MessageBoxA(NULL, "This user does not exist.", "Error", MB_OK | MB_ICONERROR);
		userExist = false;
	}
	findUser.close();
	decrypted = encryptDecrypt(password);
}

void createNewUser::newUser(std::string userName, std::string password) {
	//create a directory
	CreateDirectoryA("C:/UserAccount", NULL);
	std::string user = "C:/UserAccount/" + userName + ".txt";
	std::fstream newUser(user);

	if (newUser.is_open()) {
		MessageBoxA(NULL, "Sorry this user already exists.", "Info", MB_OK | MB_ICONINFORMATION);
		newUser.close();
	}
	else {
		newUser.open(user, std::fstream::app);
		std::string  encrypt = encryptDecrypt(password);
		newUser << encrypt << std::endl;
		newUser.close();
		MessageBoxA(NULL, "You've successfully been registered! Now try to login.", "Info", MB_OK | MB_ICONINFORMATION);
	}
}

std::string createNewUser::encryptDecrypt(std::string pw) {
	char key[5] = { 'H', 'F', 'L' , 'A', 'U' };
	std::string output = pw;

	for (int i = 0; i < pw.length(); i++) {
		output[i] = (pw[i] ^ key[i % (sizeof(key) / sizeof(key[0]))]);
	}
	return output;
}


createNewUser::~createNewUser()
{
}