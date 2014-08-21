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

//dup2 <-- gotta use dis
//pipe <-- gotta use dat

bool hasAmpersan = false;
bool inRedirect = false;
bool outRedirect = false;
bool appRedirect = false;
bool haspipe = false;

void getinput(char ** userinput)
{
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
			userinput[sizearr] = NULL;
			exit(0);
		}
		for(unsigned int i = 0; i < strlen(input); i++)
		{
			if(i == 0 && input[i] == '#')
			{
				earlyhashflag = true;
				break;
			}
			else if(input[i] == '#')
			{
				input[i] = '\0';
				hashflag = true;
				break;
			}
		}
		for(unsigned int i = 0; i < strlen(input); i++)
		{
			if(input[i] == '&')
			{
				hasAmpersan = true;
			}
		}
		if(strcmp(input, "<") == 0)
		{
			inRedirect = true;
		}
		if(strcmp(input, ">") == 0)
		{
			outRedirect = true;
		}
		if(strcmp(input, ">>") == 0)
		{
			appRedirect = true;
		}
		if(strcmp(input, "|") == 0)
		{
			haspipe = true;
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
	cout << "end of array takin" << endl;*/
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
		char** l = new char*[100]; // used for one side of the redirection (left)
		char** r = new char*[100]; // used for one side of the redirection (right)
		bool foundflag = false;
		
		if(inRedirect || outRedirect || appRedirect || haspipe){
			int i =0;
			int j =0;
			for(i = 0; *input != NULL; i++){ // loop seperate right & left
				if(strcmp(*input,"<")==0 || strcmp(*input,">")==0 ||
					strcmp(*input,">>")==0 || strcmp(*input, "|")==0)
				{
					foundflag = true;
					l[i] = NULL;
					i = 0;
					//cout << "redirection found" << endl;
				}
				else if(!foundflag){
					l[i] = *input;
					//cout << "inputing in left side" << endl;
				}
				else if(foundflag){
					r[j] = *input;
					j++;
					//cout << "inputing in right side" << endl;
				}
				input++;
			}
			//cout << "END OF ARRAY SEPERATION" << endl;
			r[j] = NULL;
		}
		if(inRedirect)
		{
			//cout << "inredirect '<'" << endl;
			freopen(r[0],"r", stdin);
		}
		else if(outRedirect)
		{
			//cout << "outdirect '>'" << endl;
			freopen(r[0],"w+",stdout);
		}
		else if(appRedirect)
		{
			//cout << "appdirect '>>'" << endl;
			freopen(r[0],"a+",stdout);
		}
		else if(haspipe)
		{
			cout << "NOT DONE YET WITH PIPING";
		}
		if(foundflag) // if special redirection
		{
			execvp(l[0],l);
			//execvp(input[0], input);
			perror("child exec failed");
		}
		else
		{						// normal making no redirection
			execvp(input[0], input);
			perror("child exec failed");
		}
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
		while(command[i] != NULL)			// empities array for new one
		{
			command[i] = NULL;
			i++;
		}
		hasAmpersan = false;
		inRedirect =false;
		outRedirect =false;
		appRedirect =false;
		haspipe = false;
	}
		return 0;
}
