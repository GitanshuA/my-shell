#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <libgen.h>
#include <fcntl.h>
#include <ctype.h>
#define CYNB "\001\e[01;36m\002"
#define RED "\001\e[00;31m\002"
#define REDB "\001\e[01;31m\002"
#define GRN "\001\e[0;32m\002"
#define YLW "\001\e[00;33m\002"
#define YLWB "\001\e[01;33m\002"
#define reset "\001\e[0m\002"
#define MAX_LENGTH 1000

char *removewhite(char *s);

bool ismyls(char *inp);
int myls(char *inp, char *cwd);
bool ismycp(char* inp);
int mycp(char *inp, char* cwd);
bool ismymv(char *inp);
int mymv(char *inp, char* cwd);
bool ismygrep(char *inp);
int mygrep(char *inp, char *cwd);
bool ismyps(char *inp);
int myps(char *inp, char* cwd);
bool ishelp(char* inp);
int help(char *inp, char *indir);

int myls_opt_checker(char *inp, bool a[], char *newdir);
int mycp_opt_checker(char *inp, bool a[], char *source, char *dest);
int mymv_opt_checker(char *inp, bool a[], char *source, char *dest);
int mygrep_opt_checker(char *inp, bool a[], char *query, char *myfile);
int myps_opt_checker(char *inp, bool a[]);