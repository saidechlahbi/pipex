#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main ()
{
    // int fd[2];
    // pid_t pid;
    // char buffer[100];

    // //create a pipe 
    // if (pipe(fd) == -1)
    // {
    //     perror("pipe\n");
    //     return (1);
    // }
    // pid = fork();
    // if (pid == -1)
    // {
    //     perror("error in fork\n");
    //     return (1);
    // }
    // if (pid == 0)
    // {
    //     const char *str = "we have alot of whores\n";
    //     close(fd[0]);
    //     write (fd[1], str, strlen(str));
    //     close(fd[1]);
    // }
    // else
    // {
    //     close (fd[1]);
    //     read(fd[0], buffer, sizeof (buffer));
    //     printf("paent receive : %s\n",buffer);
    //     close(fd[0]);
    // }



    int fd = open("file1.txt", O_RDWR);
    if (fd == -1)
    {
        perror("error\n");
        return 1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("error\n");
        return 1;
    }
    printf("hello world\n");



}