#include <iostream>
#include <fstream>
#include "sfchat.h"

using namespace std;

int main()
{
	bool working{ true };
	int answer{};
	fstream chat;
	fstream users;
	unique_ptr<User_Account> userAccount(new User_Account());
	string login{};
	string password{};
	string name{};

	cout << "Welcome to SFChat! (1) Create a account; (2) Login to account; (3) Exit. Your answer?: ";
	cin >> answer;
	switch (answer)
	{
	case 1:
	{
		cout << "Enter your login: ";
		getline(cin >> ws, login);
		cout << "Enter your password: ";
		getline(cin >> ws, password);
		cout << "Enter your name: ";
		getline(cin >> ws, name);

		userAccount->setUser_login(login);
		userAccount->setUser_password(password);
		userAccount->setUser_name(name);

		users.open("users.txt", ios::app); //open with writing from the end
		if (!users.is_open())
		{
			cerr << "Error while opening file." << endl;
			exit(EXIT_FAILURE);
		}
		users << login << endl << password << endl << name << endl;
		users.close();

		break;
	}
	case 2:
	{
		string current_fstring;

		cout << "Enter your login: ";
		getline(cin >> ws, login);

		users.open("users.txt");
		if (!users.is_open())
		{
			cerr << "Error while opening file." << endl;
			exit(EXIT_FAILURE);
		}

		while (users >> current_fstring)
		{
			if (current_fstring == login)
			{
				cout << "Enter your password: ";
				getline(cin >> ws, password);
				users.ignore();
				getline(users, current_fstring);
				if (current_fstring == password)
				{
					cout << "Successful authorization" << endl;
					
					userAccount->setUser_login(login);
					userAccount->setUser_password(password);
					getline(users, current_fstring);
					userAccount->setUser_name(current_fstring);
				}
				else
				{
					cout << "Incorrect password" << endl;
				}

			}
		}
		users.close();

		break;
	}
	case 3:
		return 0;

	default:
		cout << "Error. Try again" << endl;
	}

	cout << "\033[2J\033[1;1H";

	while (working)
	{
		cout << "Hi, " << userAccount->getUser_name() << "! What you want to do?: (1) Read a chat; (2) Write to a chat; (3) Exit. Your answer?:  ";
		cin >> answer;

		switch (answer)
		{
		case 1:
		{
			//read from a chat
			chat.open("chat.txt");
			if (!chat.is_open())
			{
				cerr << "Error while opening file." << endl;
				exit(EXIT_FAILURE);
			}
			string chat_contents{ istreambuf_iterator<char>(chat), istreambuf_iterator<char>() }; //Read all lines from chat.txt
			cout << chat_contents << endl;
			chat.close();
			cin.ignore();
			cout << "Press Enter to continue.." << endl;
			cin.get();
			cout << "\033[2J\033[1;1H";
			break;
		}

		case 2:
		{
			//write to a chat
			string user_post{};
			chat.open("chat.txt", ios::app); //open with writing from the end
			if (!chat.is_open())
			{
				cerr << "Error while opening file." << endl;
				exit(EXIT_FAILURE);
			}
			getline(cin >> ws, user_post);
			//Write down the time, username and message to chat.txt
			chat << "[" << getCurrentTime() << "] " << userAccount->getUser_name() << ": " << user_post << endl;
			chat.close();
			cout << "\033[2J\033[1;1H";
			break;
		}

		case 3:
			working = false;
			break;

		default:
			cout << "Error. Try again" << endl;
			//working = false;



			//commands for clear a screen
			//system("cls"); //windows
			//system("clear"); //linux
			//cout << "\033[2J\033[1;1H"; // ANSI escape sequence
		}
	}
	return 0;
}