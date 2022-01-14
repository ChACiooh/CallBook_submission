#include "Handler.h"

#define GO_BACK	0
#define FIND_ERROR	-1
#define INPUT_COMMAND_SUCCESS	1
#define INPUT_COMMAND_FAILED	0

enum ModeName
{
	MODE_INIT = 1,
	MODE_BROWSE_ADDRESSBOOK, MODE_BROWSE_MESSAGEBOOK, MODE_BROWSE_CALLINFO,
	MODE_ADD_PI, MODE_DELETE_PI, MODE_EDIT_PI, MODE_FIND_PI,
	MODE_SHOWD_ADBOOK, MODE_SHOWD_MBOOK, MODE_SHOWD_CINFO, MODE_BROWSE_INDEX
};

using namespace std;

Handler::Handler() : check_exit(false), state(MODE_INIT), num_of_browsing(0)
{
	// what should I write
	adBook = AddressBook();
	mBook = MessageBook();
	cInfo = CallInfo();

	adBook.Load();
	mBook.Load();
	cInfo.Load();

	states.push(state);
}

Handler::~Handler()
{
	adBook.Save();
	while (!states.empty()){
		states.pop();
	}
}

bool Handler::Handling()
{
	try
	{
		while (InputCommand() == INPUT_COMMAND_FAILED);
		if (check_exit)	return false;
		states.push(state);

		/*
		* real action
		*/
		if (state == GO_BACK)
		{
			states.pop();
			states.pop();
			state = states.top();
		}
		switch (state)
		{ 
		case MODE_BROWSE_ADDRESSBOOK:
			num_of_browsing = BrowseAddressBook();
			break;
		case MODE_SHOWD_ADBOOK:
			ShowAddressDetail(index);
			break;
		case MODE_BROWSE_MESSAGEBOOK:
			num_of_browsing = BrowseMessageBook();
			break;
		case MODE_SHOWD_MBOOK:
			ShowMessageDetail(index);
			break;
		case MODE_BROWSE_CALLINFO:
			num_of_browsing = BrowseCallInfo();
			break;
		case MODE_SHOWD_CINFO:
			ShowCallInfoDetail(index);
			break;
		case MODE_ADD_PI:
			AddPersonInfo();
			if(state == MODE_BROWSE_ADDRESSBOOK)
				num_of_browsing = BrowseAddressBook();
			break;
		case MODE_DELETE_PI:
			DeletePersonInfo(index);
			if (state == MODE_BROWSE_ADDRESSBOOK)
				num_of_browsing = BrowseAddressBook();
			break;
		case MODE_EDIT_PI:
			EditPersonInfo(index);
			if (state == MODE_BROWSE_ADDRESSBOOK)
				num_of_browsing = BrowseAddressBook();
			break;
		case MODE_FIND_PI:
			FindPersonInfo(input_name);
			break;
		}

	}
	catch (exception e) {
		return false; // got an error or more
	}

	return true; // success
} // Handling end

int Handler::InputCommand()
{
	bool check;
	do
	{
		check = false;
		cout << "\nWhat do you want to do? " << endl;
		
		if (state != MODE_INIT)
		{
			cout << "0 go back" << endl;
		}

		switch (state)
		{
		case MODE_INIT:
			cout << "0 exit" << endl;
			cout << "1 browse address book" << endl;
			cout << "2 browse message book" << endl;
			cout << "3 browse call info" << endl;
			break;
		case MODE_BROWSE_ADDRESSBOOK:
			cout << "if you want to add new address, say 'add'" << endl;
			cout << "if you want to find somenone, say 'find'" << endl;
			cout << "or, what person do you want to see in detail? say the idx" << endl;
			break;
		case MODE_SHOWD_ADBOOK:
			cout << "1 delete this info" << endl;
			cout << "2 edit this info" << endl;
			break;
		case MODE_BROWSE_MESSAGEBOOK:
			cout << "what record do you want to see in detail? say the idx" << endl;
			break;
		case MODE_BROWSE_CALLINFO:
			cout << "what record do you want to see in detail? say the idx" << endl;
			break;
		}

		cin >> command;
		if (state != MODE_BROWSE_ADDRESSBOOK)
		{
			// if the state is not in this case, it must not have characters except number.
			for (int i = 0; command[i] != '\0'; i++){
				int temp = command[i] - '0';
				if (temp < 0 || temp > 9)
				{
					check = true;
					break;
				}
			}
		}
		
		if (check)
		{
			cout << "incorrect command.\n" << endl;
		}
		else
		{
			int now_state = state;
			switch (now_state)
			{
			case MODE_INIT:
				sscanf(command.c_str(), "%d", &state);
				state++;
				if (state < MODE_BROWSE_ADDRESSBOOK || state > MODE_BROWSE_CALLINFO)
				{
					if (state == 1)
					{
						check_exit = true;
						break;
					}
					cout << "incorrect command." << endl;
					state = now_state;
					check = true;
				}
				break;
			case MODE_BROWSE_ADDRESSBOOK:
				if (command == "find")
				{
					input_name = "";
					cout << "write name : ";
					cin >> input_name;
					state = MODE_FIND_PI;
				}
				else if (command == "add")
				{
					state = MODE_ADD_PI;
				}
				else // for veiwing with index
				{
					sscanf(command.c_str(), "%d", &index);
					if (index == GO_BACK)
					{
						state = GO_BACK;
					}
					else
					{
						if (index > num_of_browsing || index < GO_BACK)
						{
							check = true;
							cout << "incorrect command." << endl;
							break;
						}
						index--;
						state = MODE_SHOWD_ADBOOK;
					}
				}
				break;
			case MODE_BROWSE_MESSAGEBOOK:
				sscanf(command.c_str(), "%d", &index);
				if (index == GO_BACK)
				{
					state = GO_BACK;
				}
				else
				{
					if (index > num_of_browsing || index < GO_BACK)
					{
						check = true;
						cout << "incorrect command." << endl;
						break;
					}
					index--;
					state = MODE_SHOWD_MBOOK;
				}
				break;
			case MODE_BROWSE_CALLINFO:
				sscanf(command.c_str(), "%d", &index);
				if (index == GO_BACK)
				{
					state = GO_BACK;
				}
				else
				{
					if (index > num_of_browsing || index < GO_BACK)
					{
						check = true;
						cout << "incorrect command." << endl;
						break;
					}
					index--;
					state = MODE_SHOWD_CINFO;
				}
				break;
			case MODE_SHOWD_ADBOOK:
				sscanf(command.c_str(), "%d", &state);
				if (state < 0 || state > 2)
				{
					check = true;
					state = now_state;
					cout << "incorrect command." << endl;
				}
				else
				{
					switch (state)
					{
					case 1:
						state = MODE_DELETE_PI;
						break;
					case 2:
						state = MODE_EDIT_PI;
						break;
					}
					break;
				}
				break;
			case MODE_SHOWD_MBOOK:
			case MODE_SHOWD_CINFO:
				sscanf(command.c_str(), "%d", &state);
				if (state != GO_BACK)
				{
					check = true;
					state = now_state;
					cout << "incorrect command." << endl;
				}
				else break;
			} // switch(now_state) end
		} // else end
	} while (check); // initial browsing end


	return INPUT_COMMAND_SUCCESS;
} // InputCommand end

int Handler::BrowseAddressBook()
{
	return adBook.Browse();
}

int Handler::BrowseMessageBook()
{
	return mBook.Browse();
}

int Handler::BrowseCallInfo()
{
	return cInfo.Browse();
}

void Handler::AddPersonInfo()
{
	string name;
	string phone_number;
	string email;
	cout << "name : ";
	cin >> name;
	cout << "phone number : ";
	cin >> phone_number;
	cout << "email : ";
	cin >> email;

	/*if (email.length() == 1 && email[0] == '0')
		email = "";*/

	PersonInfo new_person(name, phone_number, email);
	adBook.Add(new_person);

	cout << "\nadd complete\n" << endl;

	states.pop();
	state = states.top();
}

void Handler::DeletePersonInfo(int idx)
{
	adBook.Delete(idx);

	cout << "delete complete\n" << endl;
	states.pop(); // now, detail mode. but there's no data
	states.pop(); // now, correct situation
	state = states.top();
}

void Handler::EditPersonInfo(int idx)
{     
	adBook.Edit(idx);
	
	cout << "edit complete\n" << endl;
	states.pop();
	state = states.top();
}

void Handler::FindPersonInfo(string name)
{
	states.pop(); // now, it is not find mode
	num_of_browsing = adBook.Browse(name);
	if (num_of_browsing == 0)
	{
		cout << "not found\n" << endl;
	}
	state = states.top();
}

void Handler::ShowAddressDetail(int idx) const
{
	adBook.ShowDetail(idx);
}

void Handler::ShowMessageDetail(int idx) const
{
	mBook.ShowDetali(idx);
}

void Handler::ShowCallInfoDetail(int idx) const
{
	cInfo.ShowDetail(idx);
}