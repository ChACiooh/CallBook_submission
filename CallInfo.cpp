#include"CallInfo.h"

void CallInfo::Load()
{
	ifstream saveFile;
	saveFile.open("CallInfo.txt");
	CallBox getCall;
	for (int i = 0; i < 20;i ++)
	{
		saveFile >> getCall.HowCalled >> getCall.personInfo.GetName()
			>> getCall.personInfo.GetPhoneNumber() >> getCall.personInfo.GetEmail();
		callBoxes.push_back(getCall);
	}
}

int CallInfo::Browse()
{
	cout << "==========================" << endl;
	for (int i = 0; i < callBoxes.size(); i++)
	{
		cout << "No." << i + 1 << " ";
		if (callBoxes[i].HowCalled == DISPATCH)
		{
			cout << "DISPATCH ";
		}
		else
		{
			cout << "RECEIVE ";
		}
		cout << callBoxes[i].personInfo.GetName() << endl;
	}
	return callBoxes.size();
}

void CallInfo::ShowDetail(int idx) const
{
	cout << "==========================" << endl;
	callBoxes[idx].personInfo.ShowDetail();
}