/*
 * =====================================================================================
 *
 *       Filename:  log.c
 *
 *    Description:  user log
 *
 *        Version:  1.0
 *        Created:  02/17/2013
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Harold Miao, miaohonghit@gmail.com
 *
 * =====================================================================================
 */


#include "log.h"

/* ---------- internal function begin ---------- */
logoptions
creatlog(const char *name,  int option, int en_level) {
    logoptions logoption;

    /* Generate log file path and file name */
    //char base_name[] = "/tmp/";
    //size_t name_size = strlen(base_name);
    //printf("%d\n",name_size );
    size_t name_size = strlen(name);
    ++name_size;

    if (name_size > MAX_NAME_SIZE) {
        exit(ERROR_NO);
    }
    char *file_name = malloc(name_size);
    if (NULL == file_name) {
        fprintf(stderr, "%s\n", strerror(errno) );
        exit(errno);
    }
    memset(file_name, 0, name_size);

    snprintf(file_name, name_size, "%s", name);

    /* Creat file or cut exist file length */
    //int fd = creat(file_name, S_IRUSR | S_IWUSR);
    int fd = open(file_name, O_RDWR | O_APPEND | O_CREAT); 
    if (ERROR_NO == fd) {
        fprintf(stderr, "%s\n", strerror(errno) );
        exit(errno);
    }
    close(fd);

    /* Generate time */
    struct tm *ptm;
    time_t timep, time_jedge;
    char now[TIME_LEN];

    time_jedge = time(&timep);
    if (-1 == time_jedge) {
        exit(-1);
    }
    ptm = localtime(&timep);
    snprintf(now, TIME_LEN,
             "%.4d-%.2d-%.2d %.2d:%.2d:%.2d",
             ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
             ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

    /* Print header infomation to log file */
    FILE *fp = fopen(file_name, "a+");
    fprintf(fp,
            "<Enable Log> User:%d, Pid:%d, log-enable-level:%d, Start-time:%s\n",
            getuid(), getpid(), en_level, now);
    fclose(fp);

    logoption.log_file = file_name;
    return logoption;
}

int
syslog(logoptions log_set, int level, const char *format,...) {
    FILE *fp = fopen(log_set.log_file, "a+");
    if (NULL == fp) {
        return ERROR_NO;
    }

    /* Log system data */
    struct tm *ptm;
    time_t timep, time_jedge;
    char now[TIME_LEN];

    /* Generate time */
    time_jedge = time(&timep);
    if (-1 == time_jedge) {
        return ERROR_NO;
    }
    ptm = localtime(&timep);
    snprintf(now, TIME_LEN,
             "%.4d-%.2d-%.2d %.2d:%.2d:%.2d",
             ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
             ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

    /* Print header infomation to log file */
    fprintf(fp, "<User Log> Time:%s, User:%d, Pid:%d, log-level:%d ",
            now, getuid(), getpid(), level);

    /* Log user data */
    fprintf(fp, " ");
    fprintf(fp, format);
    fprintf(fp, "\n");
    fclose(fp);

    return 0;
}

