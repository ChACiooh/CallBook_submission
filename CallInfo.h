#include "PersonInfo.h"
#include "FileIO.h"

struct CallBox
{
	bool HowCalled;
	PersonInfo personInfo;
};

class CallInfo :public FileIO

{
public:
	void Load();

	CallInfo(){}
	/*
	* return the number of the lists
	* print all of the lists
	*/
	int Browse();
	//void Calling(std::string phone_number, bool whoCall);
	/*
	* print the idx-th other's information
	*/
	void ShowDetail(int idx) const;

private:
	std::vector<CallBox> callBoxes;
};