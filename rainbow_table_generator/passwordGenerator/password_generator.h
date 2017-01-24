#ifndef PASSWORD_GENERATOR_H_
#define PASSWORD_GENERATOR_H_

#include <unordered_set>

class PasswordGen{
public:
	std::unordered_set <std::string> passwords;
	PasswordGen();
	~PasswordGen();
	void password_generator(std::string);
	char* get_password();
};

#endif /* PASSWORD_GENERATOR_H_ */
