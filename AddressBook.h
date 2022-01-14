#include "PersonInfo.h"
#include "FileIO.h"

class AddressBook :public FileIO
{
public:
	AddressBook(){}

	/*
	* return the number of the lists
	* print all of the lists
	*/
	void Save();
	void Load();

	int Browse();

	/*
	* return the number of the lists
	* First of all, find the name
	*/
	int Browse(std::string name);

	/*
	* return the idx if vector<PersonInfo>[idx] has the name.
	* Nor, return -1
	*/

	/*
	* print the idx-th person's information in detail.
	*/
	void ShowDetail(int idx) const;

	void Add(PersonInfo newPersonInfo);
	void Edit(int idx);
	void Delete(int idx);

	/*
	* return the idx-th person's information
	**/
	PersonInfo GetPersonInfo(int idx);

private:
	std::vector<PersonInfo> persons;
};