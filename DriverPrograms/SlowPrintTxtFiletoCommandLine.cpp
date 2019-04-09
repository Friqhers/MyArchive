//A basic program to print an txt file slowly to the command line

#include <iostream>
#include <fstream>  //for if stream
#include <string>
#include <Windows.h>  //for sleep func
void slowPrint(std::string &str, int delay)
{	
	for (int i = 0;i < str.length();i++)
	{
		std::cout << str[i];
		Sleep(delay);
	}
	std::cout << std::endl;
}
void slowPrint(char &c, int delay)
{
	std::cout << c;
	Sleep(delay);
}
int main()
{
	/*std::string textIntro1 = "Welcome to the party!!";
	slowPrint(textIntro1, 200);
	std::string name = "Mehmet Furkan Gulmez";
	slowPrint(name, 200);*/
/*
	char c;
	std::string line;
	std::ifstream infile;
	infile.open("C:\\Users\\Fukan\\Desktop\\test.txt");
	if (!infile)
	{
		std::cout << "The input file does not exists";
		return 1;
	}
	while (std::getline(infile,line))
	{
		slowPrint(line, 80);
	}
	infile.close();	
	return 0;
}
