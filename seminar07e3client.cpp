#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/msg.h>

struct mesage{
long mtype;
    struct info {
        long pid;
        long x;
        long y;
    }inf;
};

int main()
{
    key_t key;
    int msqid, len;
    key = ftok("connection", 0);
    msqid = msgget(key, 0666);
    mesage msg;
    msg.mtype = 1;
    msg.inf.pid = (long)getpid();
    long pid = msg.inf.pid;
    scanf("%ld%ld", &msg.inf.x, &msg.inf.y);
    msgsnd(msqid, &msg, sizeof(msg.inf), 0);
    msgrcv(msqid, &msg, sizeof(msg.inf), pid, 0);
    printf("%ld", msg.inf.x);
    return 0;
}
