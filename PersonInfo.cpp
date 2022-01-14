#include "PersonInfo.h"
#include <iostream>

using namespace std;

PersonInfo::PersonInfo(std::string name_, std::string phoneNumber_, std::string email_){
	name = name_;
	phoneNumber = phoneNumber_;
	email = email_;
}
void PersonInfo::ShowDetail() const
{
	cout << "This person's name is " << name << endl;
	cout << "This person's phonenumber is " << phoneNumber << endl;
	cout << "This person's email is " << email << endl;
}