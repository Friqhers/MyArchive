#include <iostream>
#include <fstream>
#include "infixToPostfix.h"
using namespace std;

int main()
{
   infixToPostfix  InfixExp;
   string infix;
   
   ifstream infile;
   
   infile.open("C:\\Users\\Fukan\\Desktop\\MehmetFurkanGülmez\\infixData.txt");//Please change this location with respect to where you save that file.
   
   if (!infile)
   {
       cout << "Cannot open input file. Program terminates!!!" << endl;
       return 1;
   }
   
   getline(infile, infix);

   while (infile)
   {
       InfixExp.setInfix(infix);
       InfixExp.showInfix();
       InfixExp.showPostfix();
       cout << endl;   
       getline(infile, infix);
	
   }   
   infile.close();
   return 0;
}
