#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//write to a chat
	fstream chat;
	chat.open("chat.txt", ios::app); //open with writing from the end
	chat << "Writing this to a chat" << endl;
	chat.close();

	//read from a chat
	chat.open("chat.txt");
	string chat_contents
	{
		istreambuf_iterator<char>(chat), istreambuf_iterator<char>()
	};
	cout << chat_contents << endl;
	chat.close();

	//commands for clear a screen
	//system("cls"); //windows
	//system("clear"); //linux
	//cout << "\033[2J\033[1;1H"; // ANSI escape sequence

	return 0;
}