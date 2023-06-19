#include "myheaderf.h"

bool optscp[4] = {0}; // 0->'i', 1->'n', 2->'u', 3->'v'

int mycp(char *inp, char *cwd)
{
    if (strlen(inp) == 4)
    {
        printf("missing operands\n");
        return 0;
    }
    else
    {
        int bl2 = 0;
        for (int i = 0; i < 6; i++)
            optscp[i] = 0;

        char source[MAX_LENGTH], dest[MAX_LENGTH];
        source[0] = '\0';
        dest[0] = '\0';
        if (mycp_opt_checker(inp, optscp, source, dest) == 1)
            return 0;
        if (strlen(source) == 0 || strlen(dest) == 0)
        {
            printf("missing file operands\n");
            return 0;
        }
        FILE *sourcef = fopen(source, "rb");
        if (sourcef == NULL)
        {
            printf("Unable to access source file/directory\n");
            return 0;
        }
        struct stat sourcestat, deststat;
        stat(source, &sourcestat);
        FILE *destf;
        char toprdest[MAX_LENGTH];
        toprdest[0] = '\0';
        strcpy(toprdest, dest);
        if (chdir(dest) == 0)
        {
            bl2 = 1;
            if (access(basename(source), F_OK) == 0)
                bl2 = 2;
            else
            {
                destf = fopen(basename(source), "wb");
                if (dest[strlen(dest) - 1] != '/')
                    strcat(dest, "/");
                strcat(dest, basename(source));
            }
        }
        if (bl2 != 1)
        {
            chdir(cwd);
            if (bl2 == 2)
            {
                if (dest[strlen(dest) - 1] != '/')
                    strcat(dest, "/");
                strcat(dest, basename(source));
            }
            if (access(dest, F_OK) == 0)
            {
                if (optscp[0] && !optscp[2])
                {
                    char choice, *userinp = malloc(MAX_LENGTH * sizeof(char));
                    printf("'%s':file already exists\nDo you want to overwrite? (Y/n) ", dest);
                    scanf("%[^\n]%*c", userinp);
                    userinp = removewhite(userinp);
                    choice = userinp[0];
                    if (choice != 'Y' && choice != 'y')
                    {
                        printf("Operation Aborted.\n");
                        return 0;
                    }
                }
                else if (optscp[1])
                {
                    printf("'%s':file already exists\nOperation Aborted.\n", dest);
                    return 0;
                }
                else if (optscp[2])
                {
                    stat(dest, &deststat);
                    if (deststat.st_mtime > sourcestat.st_mtime)
                    {
                        printf("Destination file is newer than source file.\nOperation Aborted.\n");
                        return 0;
                    }
                    if (optscp[0])
                    {
                        char choice, *userinp = malloc(MAX_LENGTH * sizeof(char));
                        printf("'%s':file already exists\nDo you want to overwrite? (Y/n) ", dest);
                        scanf("%[^\n]%*c", userinp);
                        userinp = removewhite(userinp);
                        choice = userinp[0];
                        if (choice != 'Y' && choice != 'y')
                        {
                            printf("Operation Aborted.\n");
                            return 0;
                        }
                    }
                }
            }
            destf = fopen(dest, "wb");
        }

        if (destf == NULL)
        {
            printf("Unable to access destination file/directory\n");
            chdir(cwd);
            return 0;
        }
        if (optscp[3])
            printf("'%s' -> '%s'\n", source, dest);
        int iter;
        while (1)
        {
            iter = fgetc(sourcef);
            if (iter == EOF)
                break;
            fputc(iter, destf);
        }
        chmod(dest, sourcestat.st_mode);
        fclose(sourcef);
        fclose(destf);
        chdir(cwd);
    }
}