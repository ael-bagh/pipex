/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:52:22 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/09 16:04:11 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    execute_it(t_cmd cmd[2], char *infile, char *outfile, char **envp)
{
    int    fd[2];
    int     in;
    int     out;
    pid_t   pid;

    in = open(infile, O_RDONLY);
    if (in < 0)
        perror(strerror(errno));
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        if (in != 0)
        {
            dup2(in, STDIN_FILENO);
            close(in);
        }
        if (fd[1] != 1)
        {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);           
        }
        close(fd[0]);
        execve(cmd[0].cmd_abs_path, cmd[0].cmd_w_args, envp);
        perror(strerror(errno));
        exit(errno);
    }
    close(in);
    pid = fork();
    if (pid == 0)
    {
        if (fd[0] != 0)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
        out = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IWOTH | S_IROTH);
        if (out < 0)
        {
            perror(strerror(errno));
            exit(errno);
        }
        if (out != 1)
        {
            dup2(out, STDOUT_FILENO);
            close(out);
        }
        close(fd[1]);
        execve(cmd[1].cmd_abs_path, cmd[1].cmd_w_args, envp);
        perror(strerror(errno));
        exit(errno);
    }
    close(fd[0]);
    close(fd[1]);
    while(waitpid(-1, NULL, 0) > 0)
        ;
}