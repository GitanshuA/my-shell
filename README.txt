Author: Gitanshu Arora
Roll No.: CS22BTECH11023
============================================================================================================

This zip contains two folders 'Q1' and 'Q2' which contain the source codes for question 1 and question 2 of
the assignment respectively. To compile the code for any question, please go to the respective folder and 
execute 'make' command in the terminal. On doing this, an executable named myshell will be created
which can be made to run in the terminal by typing './myshell'.

Here is a brief summary of commands and options that I have implemented in Question 2:-

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
1) In Q2, to use the commands implemented by me, please type full command names like 'myls', 'mycp', etc.
   and not just cp, mv, etc. because my Q2 uses the same terminal that I made for Q1 and hence cp, mv, ls
   etc. will be interpreted as system commands and called using system. This is done to ensure that 'cd' 
   and other important commands work properly when trying to test the code for evaluation.
2) cd is also implemented by me as the system cd doesn't work as expected. (For 'cd', just use normal syntax)
