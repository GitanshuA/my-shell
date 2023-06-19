#include "myheaderf.h"

typedef struct fullstat
{
    char file_name[MAX_LENGTH];
    struct stat file_stat;
} fullstat;

bool opts[5] = {0}; // 0->'l', 1->'a', 2->'S', 3->'t', 4->'r'

// Comparison functions
int compare_name(const void *a, const void *b)
{
    return strcmp((((fullstat *)a)->file_name), (((fullstat *)b)->file_name));
}

int compare_S(const void *a, const void *b)
{
    if ((((fullstat *)a)->file_stat).st_size < (((fullstat *)b)->file_stat).st_size)
        return 1;
    else if ((((fullstat *)a)->file_stat).st_size > (((fullstat *)b)->file_stat).st_size)
        return -1;
    return 0;
}

int compare_t(const void *a, const void *b)
{
    if ((((fullstat *)a)->file_stat).st_mtime < (((fullstat *)b)->file_stat).st_mtime)
        return 1;
    else if ((((fullstat *)a)->file_stat).st_mtime > (((fullstat *)b)->file_stat).st_mtime)
        return -1;
    return 0;
}

// To analyse file permissions
void modanalyse(unsigned long mode)
{
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int myls(char *inp, char *cwd)
{
    for (int i = 0; i < 6; i++)
        opts[i] = 0;
    char newdir[MAX_LENGTH];
    if (myls_opt_checker(inp, opts, newdir) == 1)
        return 0;
    int filec = 0, j = 0;
    struct stat filestat;
    struct dirent *de;
    fullstat fullstats[1000];
    if (strlen(newdir) == 0)
        strcpy(newdir, ".");
    if (chdir(newdir) != 0)
    {
        printf("'%s':No such file/directory\n", newdir);
        return 0;
    }
    char *mydir = malloc((MAX_LENGTH + 1) * sizeof(char));
    getcwd(mydir, MAX_LENGTH);
    DIR *dir = opendir(mydir);
    if (dir == NULL)
    {
        printf("Can't open current directory\n");
        return 0;
    }
    while ((de = readdir(dir)) != NULL)
    {
        if (stat(de->d_name, &filestat) == -1)
        {
            printf("Error\n");
            return 0;
        }
        strcpy(fullstats[filec].file_name, de->d_name);
        fullstats[filec].file_stat = filestat;
        filec++;
    }
    closedir(dir);

    qsort(fullstats, filec, sizeof(fullstat), compare_name);

    if (opts[2])
        qsort(fullstats, filec, sizeof(fullstat), compare_S);
    else if (opts[3])
        qsort(fullstats, filec, sizeof(fullstat), compare_t);

    if (!opts[0])
    {
        for (int i = 0; i < filec; i++)
        {
            if (opts[1] || !(fullstats[(1 - 2 * opts[4]) * i + opts[4] * (filec - 1)].file_name[0] == '.'))
                printf("%s\n", fullstats[(1 - 2 * opts[4]) * i + opts[4] * (filec - 1)].file_name);
        }
    }
    else
    {
        int sum = 0;
        for (int i = 0; i < filec; i++)
        {
            if (opts[1] || !(fullstats[i].file_name[0] == '.'))
                sum += fullstats[i].file_stat.st_blocks;
        }
        sum /= 2;
        printf("total %d\n", sum);

        for (int i = 0; i < filec; i++)
        {
            if (opts[1] || !(fullstats[(1 - 2 * opts[4]) * i + opts[4] * (filec - 1)].file_name[0] == '.'))
            {
                modanalyse(fullstats[(1 - 2 * opts[4]) * i + opts[4] * (filec - 1)].file_stat.st_mode);
                printf(" %3ld ", fullstats[(1 - 2 * opts[4]) * i + opts[4] * (filec - 1)].file_stat.st_nlink);
                printf("%-10s ", getpwuid(fullstats[(1 - 2 * opts[4]) * i + opts[4] * (filec - 1)].file_stat.st_gid)->pw_name);
                printf("%-10s ", getgrgid(fullstats[(1 - 2 * opts[4]) * i + opts[4] * (filec - 1)].file_stat.st_gid)->gr_name);
                printf("%10ld ", fullstats[(1 - 2 * opts[4]) * i + opts[4] * (filec - 1)].file_stat.st_size);
                struct tm *time;
                char timeread[1000];
                time = localtime(&fullstats[(1 - 2 * opts[4]) * i + opts[4] * (filec - 1)].file_stat.st_mtime);
                strftime(timeread, 1000, "%b %d %H:%M", time);
                printf("%s  ", timeread);
                printf("%s\n", fullstats[(1 - 2 * opts[4]) * i + opts[4] * (filec - 1)].file_name);
            }
        }
    }
    chdir(cwd);
}