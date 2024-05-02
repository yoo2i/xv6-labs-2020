#include "kernel/types.h"
#include "user/user.h"

void turn(int* p) {
    close(p[1]);
    int m;
    read(p[0], &m, sizeof(int));
    printf("prime %d\n", m);

    if (m == 31) {
        close(p[0]);
        exit(0);
    } else {
        int q[2];
        pipe(q);
        if (fork() == 0) {
            turn(q);
        } else { //dad
            close(q[0]);
            int n;
            while(read(p[0], &n, sizeof(int)) != 0) {
                if (n % m != 0) {
                    write(q[1], &n, sizeof(int));
                }
            }
            close(p[0]);
            close(q[1]);
            wait((int *)0);
            exit(0);
        }
    }
}

int
main(int argc, char const *argv[])
{
    int p[2];
    pipe(p);
    if (fork() == 0) {
        turn(p);
        exit(0);
    } else {
        close(p[0]);
        for (int i = 2; i <= 35; i++) {
            write(p[1], &i ,sizeof(int));
        }
        close(p[1]);
        wait((int *)0);
        exit(0);
    }
    
}