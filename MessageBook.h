#include "PersonInfo.h"
#include "FileIO.h"

struct MessageBox
{
	bool HowSent;
	std::vector<std::string> message;
	PersonInfo personInfo;
};

class MessageBook :public FileIO
{
	// maybe this class treats the messages recieved only.
public:
	void Load();

	MessageBook(){}
	/*
	* return the number of the lists
	* print names with idxes
	*/
	int Browse();

	/*
	* print the idx-th message, other's name, and other's phone number
	*/
	void ShowDetali(int idx) const;
	
private:
	std::vector<MessageBox> messageBoxes;
};