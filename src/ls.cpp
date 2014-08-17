#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

using namespace std;

#define NOFLAG 0
#define a 2
#define l 4
#define R 8

void noFlagLs()
{
	char const *dirName = ".";
	DIR *dirp;
	if(!(dirp = opendir(dirName)))
	{
		cerr << "Error(" << errno << ") opening" << dirName << endl;		
		//ADD PERROR STATEMENT!!!!!!
	}
	dirent *direntp;
		//ADD PERROR STATEMENT!!!!!!
	while((direntp = readdir(dirp)))
	{
		if((direntp->d_name)[0] != '.')
			cout << direntp->d_name << " ";
	}
		//ADD PERROR STATEMENT!!!!!!
	closedir(dirp);
	cout << endl;
}

void aFlagLs()
{
	char const *dirName = ".";
	DIR *dirp;
	if(!(dirp = opendir(dirName)))
	{
		//ADD PERROR STATEMENT!!!!!!
		cerr << "Error(" << errno << ") opening " << dirName << endl;
	}
	dirent *direntp;
		//ADD PERROR STATEMENT!!!!!!
	while((direntp = readdir(dirp)))
	{
		cout << direntp->d_name << " ";
	}
		//ADD PERROR STATEMENT!!!!!!
	closedir(dirp);
	cout << endl;
}

void lFlagLs()
{
	char const *dirName = ".";
	DIR *dirp;
	if(!(dirp = opendir(dirName)))
	{
		//ADD PERROR STATEMENT!!!!!!
		cerr << "Error(" << errno << ") opening " << dirName << endl;
	}
	dirent *direntp;
		//ADD PERROR STATEMENT!!!!!!
	struct stat s;
	while((direntp = readdir(dirp)))
	{
		if((direntp->d_name)[0] != '.')
		{
			if((stat(direntp->d_name,&s)) == -1)
				perror("stat not called properly");
			else
			{
				if(S_ISDIR(s.st_mode))
					cout << 'd';
				else
					cout << '-';
				if(s.st_mode & S_IRUSR)
					cout << 'r';
				else
					cout << '-';
				if(s.st_mode & S_IWUSR)
					cout << 'w';
				else
					cout << '-';
				if(s.st_mode & S_IXUSR)
					cout << 'x';
				else
					cout << '-';
				
				if(s.st_mode & S_IRGRP)
					cout << 'r';
				else
					cout << '-';
				if(s.st_mode & S_IWGRP)
					cout << 'w';
				else
					cout << '-';
				if(s.st_mode & S_IXGRP)
					cout << 'x';
				else
					cout << '-';
				

				if(s.st_mode & S_IROTH)
					cout << 'r';
				else
					cout << '-';
				if(s.st_mode & S_IWOTH)
					cout << 'w';
				else
					cout << '-';
				if(s.st_mode & S_IXOTH)
					cout << 'x';
				else
					cout << '-';
				cout << " " << direntp->d_name; 
				cout << endl;
			}
		}
	}

		//ADD PERROR STATEMENT!!!!!!
	closedir(dirp);
	cout << endl;
}
int main(int argc, char **argv)
{
	if(argc == 1)
			noFlagLs();
	if(argc >= 2)
	{
		if(argv[1][0] == '-')
		{

			for(int i = 1; i < argc; ++i)
			{
				for(int j = 0; argv[i][j] != '\0'; ++j)
				{
					if(argv[i][j] == 'a')
					{
						aFlagLs();		
					}
					if(argv[i][j] == 'l')
					{
						lFlagLs();		
					}
				//	else if(argv[i][j] == 'l')
				//	else 
				//	{
							
				//	}
				}
			}
		}
	}	
	else
	{
		return 0;		
	}
}
