#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>



using namespace std;


int main()
{
	bool working{ true };
	int answer{};
	fstream chat;
	const int post_buffer_size = 256;
	char user_post[post_buffer_size];

	while (working)
	{
		cout << "What you want to do?: (1) Read a chat; (2) Write to a chat. (3) Exit. Your answer?:  ";
		cin >> answer;
		switch (answer)
		{
		case 1:
		{
			//read from a chat
			chat.open("chat.txt");
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
			//write to a chat
		{
			chat.open("chat.txt", ios::app); //open with writing from the end
			cin.ignore();
			cin.getline(user_post, post_buffer_size);

			//Calculate the current time
			time_t time = chrono::system_clock::to_time_t(chrono::system_clock::now());
			tm local_time;
			localtime_s(&local_time, &time);
			char time_buffer[100];
			strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", &local_time);
			
			//Write down the time, username and message to chat.txt
			chat << "[" << time_buffer << "] " << "TestUser: " << user_post << endl;
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