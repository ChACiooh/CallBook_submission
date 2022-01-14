#pragma once

#include "AddressBook.h"
#include "MessageBook.h"
#include "CallInfo.h"
#include <stack>
#pragma warning(disable:4996)


class Handler
{
public:
	Handler();
	~Handler();

	/*
	* main() calls only this method.
	* so it has to include actions
	* and if u want to exit, return true
	*/
	bool Handling();

private:
	AddressBook adBook;
	MessageBook mBook;
	CallInfo cInfo;

	bool check_exit; // check whether it will be exited
	int state; // this variable means the situation such as browsing address book or message book and so on
	int index; // for finding
	int num_of_browsing; // number of browsing
	std::string input_name; // for finding
	std::stack<int> states; // for realizing 'go back'
	std::string command; // assign the commands to this variable through user with 'void InputCommand()'

	/* 
	* actions are below 
	*/

	/*
	* recieve commands from console window
	* ask commands
	* return whether it recieved command successfully
	*/
	int InputCommand();

	/*
	* Browse
	*/
	int BrowseAddressBook();
	int BrowseMessageBook();
	int BrowseCallInfo();

	/*
	* use the variable 'adBook' for executing following methods
	*/
	void AddPersonInfo();
	void DeletePersonInfo(int idx);
	void EditPersonInfo(int idx);
	void FindPersonInfo(std::string name);
	

	/*
	* show detail
	*/
	void ShowAddressDetail(int idx) const;
	void ShowMessageDetail(int idx) const;
	void ShowCallInfoDetail(int idx) const;	
};