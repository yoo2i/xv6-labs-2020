#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    char **newArgv = (char **)malloc(argc * sizeof(char *));
    for (int i = 1; i < argc; i++) {
        int len = strlen(argv[i]);
        newArgv[i - 1] = (char *)malloc((len + 1) * sizeof(char));
        strcpy(newArgv[i-1], argv[i]);
    }
    char buf[512];
    char *p = buf;
    char tmp;
    while (read(0, &tmp, sizeof(char))){
        if (tmp == '\n') {
            *p++ = 0;
            newArgv[argc - 1] = (char *)malloc((strlen(buf) + 1) * sizeof(char));
            strcpy(newArgv[argc - 1], buf);
            //printf("%s\n", newArgv[argc - 1]);
            if (fork() == 0) {
                exec(argv[1], newArgv);
                exit(0);
            } else {
                wait((int *)0);
            }
            free(newArgv[argc - 1]);
            p = buf;
        } else {
            *p++ = tmp;
        }
    }
    
    exit(0);
}
