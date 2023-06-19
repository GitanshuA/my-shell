#include "myheaderf.h"

typedef struct User
{
    char host_name[MAX_LENGTH + 1];
    char user_name[1000];
} User;
User user;

int slcount(char a[])
{
    int count = 0;
    for (int i = 0; i < strlen(a); i++)
    {
        if (a[i] == '/')
            count++;
    }
    return count;
}
char *dirprint(char *cwd)
{
    char *outcwd = (char *)malloc(MAX_LENGTH * sizeof(char));
    outcwd[0] = '\0';
    strcat(outcwd, REDB);
    int scount = 0;
    if (slcount(cwd) == 1 || cwd[1] != 'h' || cwd[2] != 'o' || cwd[3] != 'm' || cwd[4] != 'e')
        strcat(outcwd, cwd);
    else
    {
        strcat(outcwd, "~");
        for (int i = 0; i < strlen(cwd); i++)
        {
            if (cwd[i] == '/')
                scount++;
            if (scount > 2)
                strncat(outcwd, &cwd[i], 1);
        }
    }
    strcat(outcwd, reset);
    strcat(outcwd, "$ ");
    return outcwd;
}

char *removewhite(char *s)
{
    bool started = 0;
    int j = 0, hcount = 0;
    char *cleaned = malloc(MAX_LENGTH * sizeof(char));
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            if (!(s[i + 1] == ' ' || i == strlen(s) - 1 || !started) || hcount % 2 == 1)
                cleaned[j++] = s[i];
        }
        else
        {
            if (s[i] == '\'' || s[i] == '"')
                hcount++;
            started = 1;
            cleaned[j++] = s[i];
        }
    }
    cleaned[j] = '\0';
    return cleaned;
}

bool iscd(char *inp)
{
    if (inp[0] == 'c' && inp[1] == 'd' && (strlen(inp) == 2 || inp[2] == ' '))
        return true;
    return false;
}

void dirchange(char *inp, char *cwd)
{
    int j = 0;
    char *newdir = malloc((MAX_LENGTH + 1) * sizeof(char));
    int i = 3;
    for (; i < strlen(inp); i++)
    {
        if (inp[i] != '"' && inp[i] != '\'')
            newdir[j++] = inp[i];
    }
    newdir[j] = '\0';
    if (strlen(inp) == 2)
    {
        strcat(newdir, "/home/");
        strcat(newdir, user.user_name);
        if (chdir(newdir))
            printf("No such file or directory\n");
    }
    else if (newdir[0] == '/')
    {
        if (chdir(newdir))
            printf("No such file or directory\n");
    }
    else
    {
        if (strcmp(cwd, "/"))
            strcat(cwd, "/");
        strcat(cwd, newdir);
        if (chdir(cwd))
            printf("No such file or directory\n");
    }
    free(newdir);
}

int main()
{
    char init_dir[4 * MAX_LENGTH];
    getcwd(init_dir, MAX_LENGTH);
    gethostname(user.host_name, MAX_LENGTH + 1);
    getlogin_r(user.user_name, 1000);
    while (1)
    {
        char *cwd = malloc((MAX_LENGTH + 1) * sizeof(char));
        getcwd(cwd, MAX_LENGTH);
        char *input = malloc(MAX_LENGTH * sizeof(char));
        char *prompt = malloc(4 * MAX_LENGTH * sizeof(char));
        prompt[0] = '\0';

        sprintf(prompt, "%s%s%s%s%s%s%s", YLWB, user.user_name, "@", user.host_name, reset, ":", dirprint(cwd));

        input = readline(prompt);
        input = removewhite(input);
        if (input[0] != '\0')
            add_history(input);
        if (!strcmp(input, "exit"))
        {
            printf("EXITING...\n");
            return 0;
        }
        else if (iscd(input))
            dirchange(input, cwd);
        else if (ismyls(input))
            myls(input, cwd);
        else if (ismycp(input))
            mycp(input, cwd);
        else if (ismymv(input))
            mymv(input, cwd);
        else if (ismygrep(input))
            mygrep(input, cwd);
        else if (ismyps(input))
            myps(input, cwd);
        else if (ishelp(input))
            help(input, init_dir);
        else
            system(input);
    }
}