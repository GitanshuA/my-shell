#include "myheaderf.h"

bool optsgrep[5] = {0}; // 0 -> 'i', 1 -> 'w', 2 -> 'n', 3 -> 'c', 4 -> 'x'

bool valid(char c, char query)
{
    if ((c == query || query == '.') && (c != '\n'))
        return true;
    return false;
}
int mygrep(char *inp, char *cwd)
{
    if (strlen(inp) == 6)
    {
        printf("missing operands\n");
        return 0;
    }
    else
    {
        for (int i = 0; i < 6; i++)
            optsgrep[i] = 0;

        char query[MAX_LENGTH], myfile[MAX_LENGTH];
        query[0] = '\0';
        myfile[0] = '\0';
        if (mygrep_opt_checker(inp, optsgrep, query, myfile) == 1)
            return 0;

        if (strlen(query) == 0 || strlen(myfile) == 0)
        {
            printf("missing file operands\n");
            return 0;
        }
        FILE *sourcef = fopen(myfile, "r");
        if (sourcef == NULL)
        {
            printf("Unable to access file/directory\n");
            return 0;
        }
        char prchk;
        while((prchk=fgetc(sourcef))!=EOF)
        {
            if(prchk!='\n' && prchk!='\t' && !isprint(prchk))
            {
                printf("Unsupported file format.\n");
                return 0;
            }
        }
        fseek(sourcef, 0, SEEK_SET);
        char *iter = NULL;
        bool toprint = 0;
        int whereend = -1;
        char myline[MAX_LENGTH];
        ssize_t check;
        size_t len = 0;
        int linenum = 0, printcount = 0;
        while ((check = getline(&iter, &len, sourcef)) != -1)
        {
            linenum++;
            toprint = 0;
            for (int i = 0; i < 1000; i++)
                myline[i] = '\0';
            for (int i = 0; i < strlen(iter) - 1; i++)
            {
                int j = i;
                if (((valid(iter[i], query[0])) || (optsgrep[0] && (toupper(iter[i]) == toupper(query[0])))) && ((!optsgrep[1]) || i == 0 || (!isalnum(iter[i - 1]))) && !(optsgrep[4] && i != 0))
                {
                    if (i + strlen(query) < strlen(iter))
                    {
                        for (; j <= strlen(query) + i - 1; j++)
                        {
                            if (!valid(iter[j], query[j - i]) && !(optsgrep[0] && (toupper(iter[j]) == toupper(query[j - i]))))
                                break;
                        }
                    }
                }
                if ((j == strlen(query) + i) && !(optsgrep[4] && (j != strlen(iter) - 1)))
                {
                    if (optsgrep[1] && ((j != strlen(iter) - 1) && (isalnum(iter[j]))))
                    {
                        if ((toprint) && !optsgrep[3])
                            printf("%c", iter[i]);
                        myline[i] = iter[i];
                        continue;
                    }
                    if (!toprint && !optsgrep[3])
                    {
                        if (optsgrep[2])
                        {
                            printf(RED "%d" reset, linenum);
                            printf(GRN ":" reset);
                        }
                        printf("%s", myline);
                    }
                    toprint = 1;
                    if (!optsgrep[3])
                    {
                        printf(CYNB);
                        for (int p = i; p <= strlen(query) + i - 1; p++)
                            printf("%c", iter[p]);
                        printf(reset);
                    }
                    i += strlen(query) - 1;
                }
                else if (!toprint)
                {
                    myline[i] = iter[i];
                }
                else if (iter[i] != '\n' && !optsgrep[3])
                    printf("%c", iter[i]);
            }
            if (toprint)
            {
                if (!optsgrep[3])
                    printf("\n");
                printcount++;
            }
        }
        if (optsgrep[3])
            printf("%d\n", printcount);
    }
}