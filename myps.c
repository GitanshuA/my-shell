#include "myheaderf.h"

bool optsps[4] = {0}; // 0 -> 'e', 1 -> 'a', 2 -> 'f', 3 -> 'd'

int myps(char *inp, char *cwd)
{
    for (int i = 0; i < 6; i++)
        optsps[i] = 0;

    if (myps_opt_checker(inp, optsps) == 1)
        return 0;

    int my_fd;
    char my_tty[MAX_LENGTH];
    my_tty[0] = '\0';
    my_fd = open("/proc/self/fd/0", O_RDONLY);
    strcpy(my_tty, ttyname(my_fd));
    close(my_fd);
    if (optsps[2])
    {
        if (optsps[0])
            printf("%-17s %-9s %-8s %2s %s %-5s\t%8s %s\n", "UID", "PID", "PPID", "C", "STIME", "TTY", "TIME", "CMD");
        else
            printf("%-8s %-9s %-8s %2s %s %-5s\t%8s %s\n", "UID", "PID", "PPID", "C", "STIME", "TTY", "TIME", "CMD");
    }
    else
        printf("%5s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");
    bool isproc = 0;
    char proc_fdpath[MAX_LENGTH], proc_stpath[MAX_LENGTH], proc_statuspath[MAX_LENGTH], readtime[MAX_LENGTH], usrname[MAX_LENGTH], readstarttime[MAX_LENGTH], proc_fullcmdpath[MAX_LENGTH], fullcmd[MAX_LENGTH];
    fullcmd[0] = '\0';
    char *cur_tty;
    int curfd;
    DIR *dir;
    struct dirent *de;
    FILE *stats, *status;
    dir = opendir("/proc");
    if (dir == NULL)
    {
        printf("Error\n");
        return 0;
    }
    int pid, ppid, sid, pgrp;
    size_t len = 1000;
    char cmd[MAX_LENGTH], state;
    unsigned long utime, stime, starttime, tot_time;
    while ((de = readdir(dir)) != NULL)
    {
        isproc = 1;
        for (int i = 0; i < strlen(de->d_name); i++)
        {
            if (!isdigit(de->d_name[i]))
            {
                isproc = 0;
                break;
            }
        }
        if (isproc)
        {
            sprintf(proc_fdpath, "/proc/%s/fd/0", de->d_name);
            curfd = open(proc_fdpath, O_RDONLY);
            cur_tty = ttyname(curfd);
            close(curfd);
            if ((cur_tty && strcmp(cur_tty, my_tty) == 0) || optsps[0] || optsps[3])
            {
                if (cur_tty == NULL)
                    cur_tty = "     ?";
                sprintf(proc_stpath, "/proc/%s/stat", de->d_name);
                stats = fopen(proc_stpath, "r");
                if (stats == NULL)
                {
                    continue;
                }
                fscanf(stats, "%d (%[^)]) %c %d %d %d %*d %*d %*u %*u %*u %*u %*u %lu %lu %*d %*d %*d %*d %*d %*u %lu", &pid, cmd, &state, &ppid, &pgrp, &sid, &utime, &stime, &starttime);
                fclose(stats);

                // Calculating TIME
                tot_time = ((utime + stime) / (double)sysconf(_SC_CLK_TCK));
                sprintf(readtime, "%02ld:%02ld:%02ld", (tot_time / 3600), (tot_time / 60) % 60, tot_time % 60);

                // Getting UID
                sprintf(proc_statuspath, "/proc/%s/status", de->d_name);
                FILE *status = fopen(proc_statuspath, "r");
                if (status == NULL)
                {
                    continue;
                }
                int uid;
                char line_iter[MAX_LENGTH];
                line_iter[0] = '\0';
                while (fgets(line_iter, sizeof(line_iter), status))
                {
                    if (sscanf(line_iter, "Uid: %d", &uid) == 1)
                    {
                        break;
                    }
                }
                fclose(status);
                struct passwd *pw = getpwuid(uid);
                strcpy(usrname, pw->pw_name);
                if(strlen(usrname)>8)
                {
                    usrname[7] = '+';
                    usrname[8] = '\0';
                }

                // Calculating STIME
                double uptime, idle;
                FILE *uptime_file = fopen("/proc/uptime", "r");
                if (uptime_file == NULL)
                {
                    continue;
                }
                fscanf(uptime_file, "%lf %lf", &uptime, &idle);
                fclose(uptime_file);
                time_t boot_time = time(NULL) - uptime;
                time_t start_time = boot_time + (starttime / sysconf(_SC_CLK_TCK));
                struct tm *start_time_struct = localtime(&start_time);
                strftime(readstarttime, 1000, "%H:%M", start_time_struct);

                // Getting full command name
                int count = 0;
                char cm;
                sprintf(proc_fullcmdpath, "/proc/%s/cmdline", de->d_name);
                FILE *cmd_file = fopen(proc_fullcmdpath, "r");
                if (cmd_file == NULL)
                {
                    continue;
                }
                while ((cm = fgetc(cmd_file)) != EOF && (!optsps[0] || count < 50) && (count < 60))
                {
                    if (cm == '\0')
                        fullcmd[count++] = ' ';
                    else
                        fullcmd[count++] = cm;
                }
                fullcmd[count] = '\0';
                if (count == 0)
                    strcpy(fullcmd, cmd);
                fclose(cmd_file);

                // Calculating C
                long int total_time_process = utime + stime;
                double cpu_usage = 100.0 * ((double)(total_time_process / (double)sysconf(_SC_CLK_TCK)) / ((double)uptime - ((double)stime / sysconf(_SC_CLK_TCK))));

                if (optsps[2] && (!((optsps[1] || optsps[3]) && !optsps[0]) || pid != sid))
                {
                    if (optsps[0])
                        printf("%-17s %-9d %-8d %2d %s %-5s\t%8s %s\n", usrname, pid, ppid, (int)cpu_usage, readstarttime, cur_tty + 5, readtime, fullcmd);
                    else
                        printf("%-8s %-9d %-8d %2d %s %-5s\t%8s %s\n", usrname, pid, ppid, (int)cpu_usage, readstarttime, cur_tty + 5, readtime, fullcmd);
                }
                else if (!((optsps[1] || optsps[3]) && !optsps[0]) || pid != sid)
                    printf("%5s %-5s\t%8s %s\n", de->d_name, cur_tty + 5, readtime, cmd);
            }
        }
    }
}