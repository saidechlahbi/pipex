/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:50:09 by sechlahb          #+#    #+#             */
/*   Updated: 2025/01/30 18:28:59 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// }











// #include <stdio.h>
// #include <unistd.h>

// int main(int ac , char **av, char **envp)
// {
//     printf("Executing ...\n");
//     int fd  = open ("file1.txt", O_RDWR);

//     dup2(fd, STDOUT_FILENO);
//     char **str = &av[1];
//     if (execve(av[1], str, envp) == -1)
//     {
//         perror ("error counting \n");
//         return (-1);
//     }
//     return 0;
// }













#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int ac, char **av, char **envp)
{
    int pipefd[2];  // Array to hold read and write pipe file descriptors
    pid_t pid;

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    
    // Create first child for ls
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {  // Child process for ls
        // Close read end
        close(pipefd[0]);
        
        // Redirect stdout to pipe write end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // Execute ls
        char *args[] = {"ls", "-la", NULL};
        execve("/bin/ls", args, envp);
        perror("execve ls");
        return 1;
    }

    // Create second child for grep
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {  // Child process for grep
        // Close write end
        close(pipefd[1]);
        
        // Redirect stdin to pipe read end
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        // Execute grep
        char *args[] = {"grep", av[4], NULL};
        execve("/bin/grep", args, envp);
        perror("execve grep");
        return 1;
    }

    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both children
    wait(NULL);
    wait(NULL);

    return 0;
}

