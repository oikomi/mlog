/*
 * =====================================================================================
 *
 *       Filename:  test_log.c
 *
 *    Description:  testing log
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


#include "../src/log.h"

int
main ( int argc, char *argv[] ) {
    logoptions tmp;

    tmp = creatlog("/tmp/mlog", 1, LOG_DEBUG);

    pid_t pid;

    pid = fork();

    if (0 == pid) {
        syslog(tmp, 6, "c First log");
        syslog(tmp, 6, "c Second log");
        syslog(tmp, 6, "c Thrid  log");
        syslog(tmp, 6, "c testing log");
    } else if (pid > 0) {
        syslog(tmp, 6, "p First log");
        syslog(tmp, 6, "p Second log");
        syslog(tmp, 6, "p Thrid  log");
        syslog(tmp, 6, "p testing log");
    } else {
        _exit(ERROR_NO);
    }


    return 0;
}				
/* ----------  end of function main  ---------- */

