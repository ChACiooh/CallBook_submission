#include"AddressBook.h"
#include<algorithm>


void AddressBook::Save()
{
	ofstream saveFile;
	saveFile.open("AddressBook.txt");
	for (unsigned i = 0; i < persons.size(); i++)
	{
		saveFile << persons[i].GetName() << " " << persons[i].GetPhoneNumber() << " " << persons[i].GetEmail();
		if (i < persons.size() - 1)saveFile << endl;
	}
}

void AddressBook::Load()
{
	ifstream saveFile;
	saveFile.open("AddressBook.txt");
	PersonInfo getPerson;
	while (saveFile.good())
	{
		saveFile >> getPerson.GetName() >> getPerson.GetPhoneNumber() >> getPerson.GetEmail();
		persons.push_back(getPerson);
	}

}

bool cmp(PersonInfo A, PersonInfo B)
{
	return A.GetName().compare(B.GetName())<0;
}

int AddressBook::Browse() 
{
	sort(persons.begin(), persons.end(), cmp);
	// we have to sort persons
	cout << "==========================" << endl;
	for (unsigned i = 0; i < persons.size(); i++)
	{
		cout << "No." << i + 1 << " ";
		cout << persons[i].GetName() << " " << persons[i].GetPhoneNumber() << " " << persons[i].GetEmail() << endl;
	}
	return persons.size();
}

int AddressBook::Browse(std::string name)
{
	sort(persons.begin(), persons.end(), cmp);
	vector<int> idxset;
	cout << "==========================" << endl;
	for (unsigned i = 0; i < persons.size(); i++)
	{
		if (persons[i].GetName() == name)
		{
			cout << "No." << i + 1 << " ";
			cout << persons[i].GetName() << " " << persons[i].GetPhoneNumber() << " " << persons[i].GetEmail() << endl;
			idxset.push_back(i);
		}
	}
	return idxset.size();
}

void AddressBook::Add(PersonInfo newPersonInfo)
{
	persons.push_back(newPersonInfo);
	Save();
}

void AddressBook::Edit(int idx)
{
	cout << "name :";
	cin >> persons[idx].GetName();

	cout << "phonenumber :";
	cin >> persons[idx].GetPhoneNumber();

	cout << "email :";
	cin >> persons[idx].GetEmail();
	Save();
}

void AddressBook::Delete(int idx)
{
	persons.erase(persons.begin()+idx); 
	Save();
}

PersonInfo AddressBook::GetPersonInfo(int idx)
{
	return persons[idx];
	Save();
}

void AddressBook::ShowDetail(int idx) const
{
	cout << "==========================" << endl;
	persons[idx].ShowDetail();
}