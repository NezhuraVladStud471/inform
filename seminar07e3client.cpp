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

/*
 * На самом деле ставить различные проверки - не самая плохая идея.
 * Если вы долго работаете над написанием программы и в один момент что-то сломали, то
 * для поиска ошибки вам надо будет заново воскрешать отладочную информации и информацию об ошибках.
 * Например, я не заглядывая в код, хочу запустить программы.
 * Конечно же, у меня нет никакого файла connection, и я долго буду гадать, что не так.
 * Также вы убрали IPC_CREAT из флагов. Т.е. пользователь должен был догадаться, что сервер надо запустить обязательно первым.
 *
 * Итого, когда пишите код, рассчитывайте, что им может кто-то воспользоваться кроме вас. И всех ваших предположений он не знает.
 *
 * Можете в клиенте ничего не править. Это пожелание на будущее. 
 */

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
