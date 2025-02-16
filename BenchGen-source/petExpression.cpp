/*
Maintained by Walter Brown
Open for modification to others in Maciej Ciesielski's team.
*/
#include "expression.h"
#include<iostream>
#include<fstream>
#include <stdio.h>
#include <unistd.h>
#include "petExpression.h"
void prompt()
{
  cout << ">>>";
}
void petExpression::verify(char file[50])
{ 
  string files;
  string location(getcwd(NULL,0));
  string filein_directory="/EqnFromVerilog/";
  string in_location=location+filein_directory;
  files=in_location+file;
  string input;
  Expression ex;
  cout<<"Your verified project is :"<<files<<endl; 
  //files=file;
  ifstream fin(files);
  while(getline(fin, input)) {
    if(input == "$exit") break;
    auto equalsSign = input.find('=');
    /* If this is an addition... */
    if(equalsSign == string::npos)
    {
      ex.add(input);
    }
    /* If this is a substitution... */
    else
    {
      /* Grab the left and right sides of the equals sign. */
      ex.substitute(input.substr(0, equalsSign), input.substr(equalsSign+1));
    }
    /* Prompt for next input. */
   // prompt();
  }
  /* Print out final result. */
  cout <<"Derived Signature input is :"<< ex <<endl;
 // return 0;
}
