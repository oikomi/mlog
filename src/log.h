/*
 * =====================================================================================
 *
 *       Filename:  log.h
 *
 *    Description:  
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


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define	MAX_NAME_SIZE 64			/* max log path length */
#define	TIME_LEN 20			/* time string length */
#define	ERROR_NO -1			/* return error value */

/* TODO: add option in log */
/* Function creatlog option macro */
#define	LOG_PID 0x01			/* log the pid with each message */

/* TODO: file pointer */
typedef struct {
    char *log_file;
    int option;
} logoptions;

/* Function creatlog level enum */
enum LOG_LEVEL {
    LOG_CRITICAL = 1, LOG_ERROR, LOG_WARNING, LOG_NOTICE, LOG_INFO, LOG_DEBUG
};

logoptions creatlog(const char *name, int option, int en_level);
int syslog(logoptions log_set, int level, const char *format, ...);

