#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char const *argv[])
{
    int p[2]; //0 -> read
    int q[2]; //1 -> write
    pipe(p);
    pipe(q);

    if (fork() == 0) {
        close(p[1]);
        close(q[0]);

        read(p[0], (void *)0, 1);
        close(p[0]);

        printf("%d: received ping\n", getpid());

        write(q[1], "p", 1);
        close(q[1]);

        exit(0);
    } else {
        close(p[0]);
        close(q[1]);

        write(p[1], "p", 1);
        close(p[1]);

        read(q[0], (void *)0, 1);
        close(q[0]);

        printf("%d: received pong\n", getpid());//均需要换行
        exit(0);
    }
}
