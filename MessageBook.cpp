#include"MessageBook.h"
#include<iostream>

using namespace std;

void MessageBook::Load()
{
	for (int i = 0; i < 20; i++)
	{
		char number[256];
		sprintf(number, "%d", i+1);

		string numberToText = string(number);
		numberToText += ".txt";

		MessageBox getMessage;
		ifstream saveFile;

		saveFile.open(numberToText,ios::in);
		saveFile >> getMessage.HowSent >> getMessage.personInfo.GetName()
			>> getMessage.personInfo.GetPhoneNumber() >> getMessage.personInfo.GetEmail();

		while (saveFile.good())
		{
			string message;
			getline(saveFile, message);
			message += "\n";
			getMessage.message.push_back(message);
			
		}
		messageBoxes.push_back(getMessage);
	}
}

int MessageBook::Browse() 
{
	cout << "==========================" << endl;
	for (unsigned i = 0; i < messageBoxes.size(); i++)
	{
		cout << "No." << i + 1 << " ";
		if (messageBoxes[i].HowSent == DISPATCH)
		{
			cout << "DISPATCH ";
		}
		else 
		{
			cout << "RECEIVE ";
		}
		cout << messageBoxes[i].personInfo.GetName() << endl;
	}
	return messageBoxes.size(); 
}

void MessageBook::ShowDetali(int idx) const
{
	cout << "==========================" << endl;
	for (int i = 0; i < messageBoxes[idx].message.size(); i++)
	{
		cout << messageBoxes[idx].message[i];
	}
}