#include <iostream>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>


using namespace std;

bool aflag = false;
bool lflag = false;
bool rflag = false;
vector<string> inputs;

int execute(string input)
{
    struct stat buff;
    struct stat path;
    struct passwd *pw;
    struct group *grp;
    const char *entry = input.c_str();
    
    if (stat(entry, &buff) == -1) 
    {
        cerr <<"ls: " <<input <<": No such file or directory" <<endl;
        return 0;
    }
    
    //establishes type of file
	string filetype;
	switch (buff.st_mode & S_IFMT) 
	{
		case S_IFBLK:  filetype = "block device";          break;
		case S_IFCHR:  filetype = "character device";        break;
		case S_IFDIR:  filetype = "directory";               break;
		case S_IFIFO:  filetype = "FIFO/pipe";               break;
		case S_IFLNK:  filetype = "symlink";                 break;
		case S_IFREG:  filetype = "regular file";            break;
		case S_IFSOCK: filetype = "socket";                  break;
		default:       filetype = "unknown";                break;
	}
	//DIR *dirp;
    //struct dirent *dp;    
    
    //dirp = opendir(c);
    // looks to see if the directory given by the user is invalid
    if(opendir(entry) == NULL && filetype == "directory")
    {
        cerr <<"ls: " <<input <<": No such file or directory" <<endl;
        return 0;
    }
    
    // if the input given is a file then output info about just that file
    if(filetype == "regular file")
    {
        stat(input.c_str(), &buff);
        string x = ctime(&buff.st_mtime);
		string str = x.substr(4,12);

        string user = "";
        string group = "";
        
        int ct1 = 0;
        int ct2 = 0;
        if((grp = getgrgid(buff.st_gid))!= NULL)
        {
            group = grp->gr_name;
        }
        
        if((pw = getpwuid(buff.st_uid))!= NULL)
        {
            user = pw->pw_name;
        }
        
        if(S_ISDIR(buff.st_mode))
            ct1++;
        if(buff.st_mode & S_IXUSR)
            ct2++;
        if(lflag){
            if(S_ISDIR(buff.st_mode))
            {
                cout <<"d";
                //ct1++;
            }
            else
                cout <<"-";
            if(buff.st_mode & S_IRUSR)
                cout <<"r";
            else
                cout <<"-";
            if(buff.st_mode & S_IWUSR)
                cout <<"w";
            else
                cout <<"-";
            if(buff.st_mode & S_IXUSR)
            {
                cout <<"x";
                //ct2++;
            }
            else
                cout <<"-";
            if(buff.st_mode & S_IRGRP)
                cout <<"r";
            else
                cout <<"-";
            if(buff.st_mode & S_IWGRP)
                cout <<"w";
            else
                cout <<"-";
            if(buff.st_mode & S_IXGRP)
                cout <<"x";
            else
                cout <<"-";
            if(buff.st_mode & S_IROTH)
                cout <<"r";
            else
                cout <<"-";
            if(buff.st_mode & S_IWOTH)
                cout <<"w";
            else
                cout <<"-";
            if(buff.st_mode & S_IXOTH)
                cout <<"x";
            else
                cout <<"-";
            cout <<right <<buff.st_nlink <<" " <<setw(5) <<right <<user
                 <<setw(1) <<" " <<group <<" " <<setw(5) <<buff.st_size
                 <<" " << str <<" " <<input;
        }
        else{
            cout << input;
        }
        if(ct1 == 1)
            cout <<"/";
        if(ct2 == 1)
            cout <<"*";
        if(lflag){
            cout <<endl;
        }
        else{
            cout << "  ";
        }
    }
    

    if(filetype == "directory")
    {
        DIR *dirp;
        struct dirent *d;
        vector<string> vektor;
        vector<string> names;
        vector<string> directories;
        
        dirp = opendir(entry);
        
        if(dirp == NULL) 
        {
            cerr <<"Cannot open" <<entry <<endl;
            return -1;
        }
        
        int indent = 0;
        int bits = 0;
        int block = 0;
        //for formatting

        d = readdir(dirp);
        //output was off
        
        
        //push all directories and files in vector
        while(d != NULL)
        {
            char ch[1000];
            strcpy(ch, entry);
            strcat(ch, "/");
            strcat(ch, d->d_name);

            if(d->d_name[0] != '.' || aflag){
                names.push_back(d->d_name);
                vektor.push_back(ch);
                if ((stat(ch, &path)) == -1) 
                {
                    cerr <<"stat: failed to find file or directory" <<endl;
                    exit(0);
                }
                lstat(d->d_name, &path);
                block += path.st_blocks;
                switch (path.st_mode & S_IFMT) 
                {
                    case S_IFDIR: directories.push_back(ch);
                }
                
                if(bits < path.st_size)
                {
                    bits = path.st_size;
                }
            }
            d = readdir(dirp);        
        }
        /*if(vektor.size() == 0 && directories.size() == 0)
        {
            return 0;
        }*/
        //sorts everything
        sort(vektor.begin(),vektor.end());
        if(rflag){
            reverse(vektor.begin(), vektor.end());
        }
        //formats spacing
        while(bits != 0)
        {
            bits /= 10;
            indent++;
        }
        
        sort(names.begin(),names.end());
        if(rflag){
            reverse(names.begin(), names.end());
        }
        //sort(directories.begin(), directories.end());
        
        //output info
        if(inputs.size() != 0) cout <<input <<":" <<endl;
        if(lflag){
            cout <<"total " <<block/2 <<endl;
        }
        for(unsigned i =0; i< vektor.size(); i++)
        {
            stat(vektor.at(i).c_str(), &path);
            string a = ctime(&path.st_mtime);
            //int f = 0;
            string str = a.substr(4,12);
            int c3 = 0;
            int c4 = 0;
            string user = "";
            string group = "";
            pw = getpwuid(path.st_uid);
            if(pw != NULL)
            {
                user = pw->pw_name;
            }
            grp = getgrgid(path.st_gid);
            if(grp!= NULL)
            {
                group = grp->gr_name;
            }
            if(S_ISDIR(path.st_mode))
                c3++;
            if(path.st_mode & S_IXUSR)
                c4++;
            if(lflag)
            {
                if(S_ISDIR(path.st_mode))
                    cout <<"d";
                else
                    cout <<"-";
                if(path.st_mode & S_IRUSR)
                    cout <<"r";
                else
                    cout <<"-";
                if(path.st_mode & S_IWUSR)
                    cout <<"w";
                else
                    cout <<"-";
                if(path.st_mode & S_IXUSR)
                    cout <<"x";
                else
                    cout <<"-";
                if(path.st_mode & S_IRGRP)
                    cout <<"r";
                else
                    cout <<"-";
                if(path.st_mode & S_IWGRP)
                    cout <<"w";
                else
                    cout <<"-";
                if(path.st_mode & S_IXGRP)
                    cout <<"x";
                else
                    cout <<"-";
                if(path.st_mode & S_IROTH)
                    cout <<"r";
                else
                    cout <<"-";
                if(path.st_mode & S_IWOTH)
                    cout <<"w";
                else
                    cout <<"-";
                if(path.st_mode & S_IXOTH)
                    cout <<"x";
                else
                    cout <<"-";
                cout <<" ";
                cout <<right <<path.st_nlink <<" " <<setw(4) <<right <<user
                     <<setw(1) <<" " <<group <<" " <<setw(indent)
                     <<path.st_size <<" " <<str <<" " <<names.at(i);
            }
            else
            {
                cout << names.at(i);
            }
            if(c3 == 1)
                cout <<"/";
            else if(c4 == 1)
                cout <<"*";
            if(lflag)
                cout <<endl;
            else
                cout << "  ";
        }
        
        closedir(dirp);

    }
    cout << endl;
    return 0;
}

int main(int argc, char *argv[]) 
{
    char* found;        //will be used to see if -a,l,R is found
    if (argc >= 2)
    {
        for(int i =1; i < argc; i++)
        {
            found = strchr(argv[i], '-');
            //cout << argv[i]-found << endl;
            if(0 == argv[i]-found) // if '-' is found
            {
                if(strchr(argv[i], 'a') != NULL)
                {           // if -a is found
                    aflag = true;
                    //cout << "a flag is true" << endl;
                }
                if(strchr(argv[i], 'l') != NULL)
                {
                    lflag = true;
                    //cout << "l flag is true" << endl;
                }
                if(strchr(argv[i], 'R') != NULL)
                {
                    rflag = true;
                    //cout << "r flag is true" << endl;
                }
                for(unsigned int j = 1; j < strlen(argv[i]); j++){
                    if((argv[i])[j] != 'a' && (argv[i])[j] != 'l' &&
                       (argv[i])[j] != 'R'){
                        cout << "Invalid flags" << endl;
                        return 1;
                    }
                }
            }
            else
            {
                // everything else is considered a file/dir name
                inputs.push_back(argv[i]);
            }
        }
        if(inputs.size() == 0)
        {
            execute(".");
        }
        else
        {
            sort(inputs.begin(), inputs.end());
            if(rflag){
                reverse(inputs.begin(), inputs.end());
            }
            for(unsigned int i = 0; i < inputs.size(); i++)
            {
                execute(inputs.at(i));
            }
        }
    }
    if(argc == 1)
    {
        //print out regular ls
        execute(".");
    }
    return 0;
}
