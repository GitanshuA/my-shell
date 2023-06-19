Author: Gitanshu Arora
Roll No.: CS22BTECH11023
============================================================================================================

To compile the code, please execute 'make' command in the terminal. On doing this, an executable named myshell will be created
which can be made to run in the terminal by typing './myshell'.

Here is a brief summary of commands and options that I have implemented:-

COMMAND        OPTIONS
myls           -l, -a, -S, -t, -r
mycp           -i, -n, -u, -v
mymv           -i, -n, -u, -v 
mygrep         -i, -w, -n, -c, -x
myps           -e, -a, -f, -d 

Also these options can be used in any combination, e.g. -win, -Sr, -ef, etc. So, effectively many options are
available for each command.
For further info about these commands, type 'help' in myshell.

NOTE:-
1) To use the commands implemented by me, please type full command names like 'myls', 'mycp', etc.
   and not just cp, mv, etc. because they will be interpreted as system commands and called using system. This is done to ensure that 'cd' 
   and other important commands work properly when using the terminal.
2) cd is also implemented by me as the system cd doesn't work as expected. (For 'cd', just use normal syntax)
