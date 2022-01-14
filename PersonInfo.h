#pragma once
#include <vector>
#include <string>
#define DISPATCH 0
#define RECEIVE 1

class PersonInfo
{
public:
	PersonInfo(){} // if you don' need this, u can erase this
	PersonInfo(std::string name_, std::string phoneNumber_, std::string email_); // constructor

	void ShowDetail() const; // show the information that includes all of instances in this class
	std::string& GetName(){ return name; }
	std::string& GetPhoneNumber(){ return phoneNumber; }
	std::string& GetEmail(){ return email; }

private:
	std::string name;
	std::string phoneNumber;
	std::string email;
};
