#include <cstdlib>
#include <string>
#include <algorithm>
#include "password_generator.h"
#include "../info.h"

using namespace std;

char pcharSet[charSetLen] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@' };


void PasswordGen::password_generator(string cur) {
	if (cur.length() == maxPwLen){
		random_shuffle(cur.begin(), cur.end());
		auto p = passwords.emplace(cur);
		while (!p.second){
			random_shuffle(cur.begin(), cur.end());
			p = passwords.emplace(cur);
		}
	}else if (passwords.size() < chainCount){
		for (int i = 0; i < charSetLen; i++){
			string oldCur = cur;
			cur += pcharSet[i];
			password_generator(cur);
			cur = oldCur;
		}
	}
}

char* PasswordGen::get_password(){
	string password = *passwords.begin();
	char *passwd = (char *)malloc(sizeof(char)* 6);
	strncpy(passwd, password.c_str(), 6);
	passwords.erase(passwords.begin());
	return passwd;
}

PasswordGen::PasswordGen(){}

PasswordGen::~PasswordGen(){}