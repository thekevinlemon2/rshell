rshell
======
<<<<<<< HEAD
general:
	This program mimics the bash shell by taking in commands and performing their tasks as usual. You can perfrom tasks such as 
	-ls -lists the files in a directory
			-with all flags
	-cat -displays everything in a file
	-echo -prints out what is passed in as a parameter
	-mkdir -makes a new directory
	-# -everything after this is a comment and does not get executed
	-& -runs program in background allowing terminal to continue
	-exit -typing exit will kill the program
	-rm -removes a file
	-rmdir -removes a directory
	-for more features view the /bin page on your computer

UPDATE:
	-the ls command has now been written
		-ls can take the parameters [no parameters],[-a],[-l],[-R] and any combination on them all
		-ls can also take file names which will output the contents inside the files or directories

how to run rshell:
	-type make, this will build and compile the program
	-to run, type bin/rshell
	-to clean the file, you type make clean and this will discard executibles and object files

how to run the ls command:
	-type make, this will build both rshell and ls
	-type bin/ls [argument lists]

bugs:
	-when an error is produced, it sometimes gets printed on the line with the "$" and the next line does not have a "$", just need to hit enter again
	-# right after a command does not work properly
		-for example (ls# -a) will not execute ls
	-when "exit" is typed, sometimes it will need to be typed twice, but it will still exit
	-ls -al does not work properly and all other forms of combinations
	-ls -R does not work at all
=======
>>>>>>> 530f68e4815a4d19902652cb2f6fda19ef4f6c7b
