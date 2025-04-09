#include <chrono>
#include <ctime>
#include "sfchat.h"

User_Account::User_Account()
{
}

User_Account::User_Account(string user_login, string user_password, string user_name)
{
	this->user_login = user_login;
	this->user_password = user_password;
	this->user_name = user_name;
}

User_Account::~User_Account()
{
}

string User_Account::getUser_login() const
{
	return user_login;
}

void User_Account::setUser_login(string value)
{
	user_login = value;
}

string User_Account::getUser_password() const
{
	return user_password;
}

void User_Account::setUser_password(string value)
{
	user_password = value;
}

string User_Account::getUser_name() const
{
	return user_name;
}

void User_Account::setUser_name(string value)
{
	user_name = value;
}

string getCurrentTime()
{
	string current_time{};
	time_t time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	tm local_time;
	localtime_s(&local_time, &time);
	char time_buffer[100];
	strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", &local_time);
	current_time = time_buffer;
	
	return current_time;
}
