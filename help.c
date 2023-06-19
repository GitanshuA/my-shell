#include "myheaderf.h"

int help(char *inp, char *indir)
{
    char mindir[4*MAX_LENGTH];
    strcpy(mindir, indir);
    FILE *helpfile;
    char line[MAX_LENGTH + 1];
    if (!strcmp(inp, "help"))
    {
        strcat(mindir, "/help_pages/help_help.txt");
        helpfile = fopen(mindir, "r");
        if (helpfile == NULL)
        {
            printf("Unable to open file.\n");
            return 0;
        }
        while (fgets(line, MAX_LENGTH, helpfile) != NULL)
            printf("%s", line);
        fclose(helpfile);
    }
    else if (!strcmp(inp, "help myls"))
    {
        strcat(mindir, "/help_pages/myls_help.txt");
        helpfile = fopen(mindir, "r");
        if (helpfile == NULL)
        {
            printf("Unable to open file.\n");
            return 0;
        }
        while (fgets(line, MAX_LENGTH, helpfile) != NULL)
            printf("%s", line);
        fclose(helpfile);
    }
    else if (!strcmp(inp, "help mycp"))
    {
        strcat(mindir, "/help_pages/mycp_help.txt");
        helpfile = fopen(mindir, "r");
        if (helpfile == NULL)
        {
            printf("Unable to open file.\n");
            return 0;
        }
        while (fgets(line, MAX_LENGTH, helpfile) != NULL)
            printf("%s", line);
        fclose(helpfile);
    }
    else if (!strcmp(inp, "help mymv"))
    {
        strcat(mindir, "/help_pages/mymv_help.txt");
        helpfile = fopen(mindir, "r");
        if (helpfile == NULL)
        {
            printf("Unable to open file.\n");
            return 0;
        }
        while (fgets(line, MAX_LENGTH, helpfile) != NULL)
            printf("%s", line);
        fclose(helpfile);
    }
    else if (!strcmp(inp, "help mygrep"))
    {
        strcat(mindir, "/help_pages/mygrep_help.txt");
        helpfile = fopen(mindir, "r");
        if (helpfile == NULL)
        {
            printf("Unable to open file.\n");
            return 0;
        }
        while (fgets(line, MAX_LENGTH, helpfile) != NULL)
            printf("%s", line);
        fclose(helpfile);
    }
    else if (!strcmp(inp, "help myps"))
    {
        strcat(mindir, "/help_pages/myps_help.txt");
        helpfile = fopen(mindir, "r");
        if (helpfile == NULL)
        {
            printf("Unable to open file.\n");
            return 0;
        }
        while (fgets(line, MAX_LENGTH, helpfile) != NULL)
            printf("%s", line);
        fclose(helpfile);
    }
    else
    {
        printf("Invalid Arguments.\nFor info on how to use help, just type 'help'\n");
    }
}