#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// int main (int ac , char **av, char **envp)
// {
    //////// understand  fork function andhow it work //////////

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


//////// understand dup2 and how it work //////////////


//     int fd = open("file1.txt", O_RDWR);
//     if (fd == -1)
//     {
//         perror("error\n");
//         return 1;
//     }
//     if (dup2(fd, STDOUT_FILENO) == -1)
//     {
//         perror("error\n");
//         return 1;
//     }
//     printf("hello world\n");

// ///// undestand execve() and how it work 

//     (void)ac;
//     if (execve(av[1],av, envp) == -1)
//     {
//         perror("error founding \n");
//         return (-1);
//     }
//     return (1);

#include <stdio.h>
#include <unistd.h>

int main(int ac , char **av, char **envp)
{
    //char *argv[] = {"/bin/ls", "-l", NULL}; // Arguments for ls -l
   // char *envp[] = {NULL};                  // Use default environment

    printf("Executing /bin/ls...\n");
    // while (i < 10)
    //     printf("%s\n",envp[i++]);
    int fd  = open ("file1.txt", O_RDWR);

    // dup2(fd, STDOUT_FILENO);

    if (execve(av[1], &av[1], envp) == -1)
    {
        perror ("error counting \n");
        return (-1);
    }
    
    // Replace the current process with /bin/ls

    return 0; // This will never execute if execve is successful
}

// }