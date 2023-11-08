#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("p1 (PID: %d, PPID: %d)\n", getpid(), getppid());

    pid_t p2_pid = fork();

    if (p2_pid == -1) {
        perror("Failed to create p2");
        return 1;
    }

    if (p2_pid == 0) {
        printf("p2 (PID: %d, PPID: %d)\n", getpid(), getppid());

        pid_t p3_pid = fork();

        if (p3_pid == -1) {
            perror("Failed to create p3");
            return 1;
        }

        if (p3_pid == 0) {
            printf("p3 (PID: %d, PPID: %d)\n", getpid(), getppid());
        } else {
            wait(NULL);
        }
    } else {
        pid_t p4_pid = fork();

        if (p4_pid == -1) {
            perror("Failed to create p4");
            return 1;
        }

        if (p4_pid == 0) {
            printf("p4 (PID: %d, PPID: %d)\n", getpid(), getppid());

            sleep(2);

            printf("p4 (PID: %d, PPID: %d) has become an orphan\n", getpid(), getppid());

            sleep(10);
        } else {
            pid_t p5_pid = fork();

            if (p5_pid == -1) {
                perror("Failed to create p5");
                return 1;
            }

            if (p5_pid == 0) {
                printf("p5 (PID: %d, PPID: %d)\n", getpid(), getppid());
                exit(0);
            } else {
                wait(NULL);
            }

            sleep(1);
            printf("p1 (PID: %d) has waited for p4 (PID: %d) to become an orphan\n", getpid(), p4_pid);
            wait(NULL);
        }
    }

    return 0;
}
