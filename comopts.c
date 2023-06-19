#include "myheaderf.h"

bool ismyls(char *inp)
{
    if (inp[0] == 'm' && inp[1] == 'y' && inp[2] == 'l' && inp[3] == 's' && (strlen(inp) == 4 || inp[4] == ' '))
        return true;
    return false;
}

int myls_opt_checker(char *inp, bool a[], char *newdir)
{
    bool opttake = 0;
    int j = 0, hcount = 0;
    for (int i = 5; i < strlen(inp); i++)
    {
        if (inp[i] == ' ')
            opttake = 0;
        if (inp[i] == '-' && inp[i - 1] == ' ')
            opttake = 1;
        else if (opttake)
        {
            switch (inp[i])
            {
            case 'l':
                a[0] = 1;
                break;
            case 'a':
                a[1] = 1;
                break;
            case 'S':
                a[2] = 1;
                if (a[3] == 1)
                    a[3] = 0;
                break;
            case 't':
                a[3] = 1;
                if (a[2] == 1)
                    a[2] = 0;
                break;
            case 'r':
                a[4] = 1;
                break;
            default:
                printf("invalid option -> '%c'\n", inp[i]);
                return 1;
            }
        }
        else if (inp[i] != ' ' || hcount % 2 == 1)
        {
            if (inp[i] == '\'' || inp[i] == '"')
                hcount++;
            else    
            newdir[j++] = inp[i];
        }
    }
    newdir[j] = '\0';
}

bool ismycp(char *inp)
{
    if (inp[0] == 'm' && inp[1] == 'y' && inp[2] == 'c' && inp[3] == 'p' && (strlen(inp) == 4 || inp[4] == ' '))
        return true;
    return false;
}

int mycp_opt_checker(char *inp, bool a[], char *source, char *dest)
{
    bool opttake = 0;
    int j = 0, k = 0, hcount = 0;
    bool bl = 0;
    for (int i = 5; i < strlen(inp); i++)
    {
        if (inp[i] == ' ')
            opttake = 0;
        if (inp[i] == '-' && inp[i - 1] == ' ')
            opttake = 1;
        else if (opttake)
        {
            switch (inp[i])
            {
            case 'i':
                a[0] = 1;
                a[1] = 0;
                a[2] = 0;
                break;
            case 'n':
                a[1] = 1;
                a[0] = 0;
                a[2] = 0;
                break;
            case 'u':
                a[2] = 1;
                break;
            case 'v':
                a[3] = 1;
                break;
            default:
                printf("invalid option -> '%c'\n", inp[i]);
                return 1;
            }
        }
        else if (inp[i] != ' ' || hcount % 2 == 1)
        {
            if (inp[i] == '\'' || inp[i] == '"')
                hcount++;
            else if (!bl)
                source[j++] = inp[i];
            else
            {
                dest[k++] = inp[i];
            }
            if (i < strlen(inp) - 1 && inp[i + 1] == ' ' && hcount % 2 == 0)
                bl = 1;
        }
    }
    source[j] = '\0';
    dest[k] = '\0';
}

bool ismymv(char *inp)
{
    if (inp[0] == 'm' && inp[1] == 'y' && inp[2] == 'm' && inp[3] == 'v' && (strlen(inp) == 4 || inp[4] == ' '))
        return true;
    return false;
}

int mymv_opt_checker(char *inp, bool a[], char *source, char *dest)
{
    bool opttake = 0;
    int j = 0, k = 0, hcount = 0;
    bool bl = 0;
    for (int i = 5; i < strlen(inp); i++)
    {
        if (inp[i] == ' ')
            opttake = 0;
        if (inp[i] == '-' && inp[i - 1] == ' ')
            opttake = 1;
        else if (opttake)
        {
            switch (inp[i])
            {
            case 'i':
                a[0] = 1;
                a[1] = 0;
                a[2] = 0;
                break;
            case 'n':
                a[1] = 1;
                a[0] = 0;
                a[2] = 0;
                break;
            case 'u':
                a[2] = 1;
                break;
            case 'v':
                a[3] = 1;
                break;
            default:
                printf("invalid option -> '%c'\n", inp[i]);
                return 1;
            }
        }
        else if (inp[i] != ' ' || hcount % 2 == 1)
        {
            if (inp[i] == '\'' || inp[i] == '"')
                hcount++;
            else if (!bl)
                source[j++] = inp[i];
            else
            {
                dest[k++] = inp[i];
            }
            if (i < strlen(inp) - 1 && inp[i + 1] == ' ' && hcount % 2 == 0)
                bl = 1;
        }
    }
    source[j] = '\0';
    dest[k] = '\0';
}

bool ismygrep(char *inp)
{
    if (inp[0] == 'm' && inp[1] == 'y' && inp[2] == 'g' && inp[3] == 'r' && inp[4] == 'e' && inp[5] == 'p' && (strlen(inp) == 6 || inp[6] == ' '))
        return true;
    return false;
}

int mygrep_opt_checker(char *inp, bool a[], char *query, char *myfile)
{
    bool opttake = 0;
    int j = 0, k = 0, hcount = 0;
    bool bl = 0;
    for (int i = 7; i < strlen(inp); i++)
    {
        if (inp[i] == ' ')
            opttake = 0;
        if (inp[i] == '-' && inp[i - 1] == ' ')
            opttake = 1;
        else if (opttake)
        {
            switch (inp[i])
            {
            case 'i':
                a[0] = 1;
                break;
            case 'w':
                a[1] = 1;
                break;
            case 'n':
                a[2] = 1;
                break;
            case 'c':
                a[3] = 1;
                break;
            case 'x':
                a[4] = 1;
                break;
            default:
                printf("invalid option -> '%c'\n", inp[i]);
                return 1;
            }
        }
        else if (inp[i] != ' ' || hcount % 2 == 1)
        {
            if (inp[i] == '\'' || inp[i] == '"')
                hcount++;
            else if (!bl)
                query[j++] = inp[i];
            else
            {
                myfile[k++] = inp[i];
            }
            if (i < strlen(inp) - 1 && inp[i + 1] == ' ' && hcount % 2 == 0)
                bl = 1;
        }
    }
    query[j] = '\0';
    myfile[k] = '\0';
}

bool ismyps(char *inp)
{
    if (inp[0] == 'm' && inp[1] == 'y' && inp[2] == 'p' && inp[3] == 's' && (strlen(inp) == 4 || inp[4] == ' '))
        return true;
    return false;
}

int myps_opt_checker(char *inp, bool a[])
{
    bool opttake = 0;
    for (int i = 5; i < strlen(inp); i++)
    {
        if (inp[i] == ' ')
            opttake = 0;
        else if (inp[i] == '-' && inp[i - 1] == ' ')
            opttake = 1;
        else if (opttake)
        {
            switch (inp[i])
            {
            case 'e':
                a[0] = 1;
                break;
            case 'a':
                a[1] = 1;
                break;
            case 'f':
                a[2] = 1;
                break;
            case 'd':
                a[3] = 1;
                break;
            default:
                printf("invalid option -> '%c'\n", inp[i]);
                return 1;
            }
        }
    }
}

bool ishelp(char *inp)
{
    if (inp[0] == 'h' && inp[1] == 'e' && inp[2] == 'l' && inp[3] == 'p' && (strlen(inp) == 4 || inp[4] == ' '))
        return true;
    return false;
}
