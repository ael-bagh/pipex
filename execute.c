/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:52:22 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/09 19:12:53 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exc1(int fd[2], int in, t_cmd cmd[2], char**envp)
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

void	exc2(int fd[2], char *outfile, t_cmd cmd[2], char**envp)
{
	int	out;

	if (fd[0] != 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	out = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR
			| S_IWGRP | S_IRGRP | S_IWOTH | S_IROTH);
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

void	execute_it(t_cmd cmd[2], char *infile, char *outfile, char **envp)
{
	int		fd[2];
	int		in;
	pid_t	pid;

	in = open(infile, O_RDONLY);
	if (in < 0)
	{
		open(outfile, O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR
			| S_IWGRP | S_IRGRP | S_IWOTH | S_IROTH);
		perror(strerror(errno));
		exit(errno);
	}
	pipe(fd);
	pid = fork();
	if (pid == 0)
		exc1(fd, in, cmd, envp);
	close(in);
	pid = fork();
	if (pid == 0)
		exc2(fd, outfile, cmd, envp);
	close(fd[0]);
	close(fd[1]);
	while (waitpid(-1, NULL, 0) > 0)
		;
}
