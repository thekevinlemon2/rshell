#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string>
#include <vector>
#include <errno.h>
#include <fstream>
#include <cmath>

using namespace std;

bool hasAmpersan = false;

void getinput(char ** userinput){
	cout<< "$ ";
	char input[100];
	int sizearr = 0;
	bool hashflag = false;
	bool earlyhashflag = false;
	
	while(true)
	{
		cin >> input;		// get input
		if(strcmp(input, "exit") == 0)		// if exit is inputted, terminal ends
		{
			//cout << "EXITING NOW" << endl;
			userinput[sizearr] = NULL;
			exit(0);
		}
		for(int i = 0; i < strlen(input); i++)
		{
			if(i == 0 && input[i] == '#')
			{
				//cout << "EARLY HASHY" << endl;
				earlyhashflag = true;
				break;
			}
			else if(input[i] == '#')
			{		// loop goes through input and
				//cout << "mid hashy" << endl;
				input[i] = '\0';
				hashflag = true;
				break;
			}
		}
		for(int i = 0; i < strlen(input); i++)
		{
			if(input[i] == '&')
			{
				hasAmpersan = true;
			}
		}
		if(!hasAmpersan && !earlyhashflag)
		{
			char * temp = new char[strlen(input)+1];	//adds new char pointer
			strcpy(temp, input);
			userinput[sizearr] = temp;
			sizearr++;
		}
		if(hashflag)
		{
			//cout << "mid hashflag no more in array pls" << endl;
			hashflag = false;	// if # is entered then stop command line
			while(cin >> input){
				if(cin.get() == '\n') break;
			}
			break;
		}
		if(cin.get() == '\n')
		{
			break;		// if enter is pressed end command line
		}
	}
	userinput[sizearr] = NULL;
	/*cout << "size of arr: " << sizearr << endl;
	while(*userinput != NULL)
	{ 
		cout<< "Input: " << *userinput << endl;
		userinput++;
	}
	cout << "end of array takin" << endl;
	* */
}


void run(char ** input)
{
	int pid = fork();
	//error check
	if (pid == -1)
	{
		perror("failed to fork");
	}
	else if (pid == 0) //child
	{
		execvp(input[0], input);
		perror("child exec failed");
	}
	else //parent function
	{
		if (hasAmpersan == false)
		{
			wait(0);
		}
	}
}
		


int main (int argc, char *argv[])
{
	while(true)
	{
		char * command[100];
		getinput(command);
		run(command);
		int i = 0;
		while(command[i] != NULL)
		{
			command[i] = NULL;
			i++;
		}
		hasAmpersan = false;
	}
		return 0;
}
