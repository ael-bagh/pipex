/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:59:21 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/09 15:53:34 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *path, char *cmd)
{
	char	**exec_paths;
	char	*abs_path;
	char	*tmp;
	int		i;
	int		ret;

	i = -1;
	exec_paths = ft_split(path, ':');
	while (exec_paths[++i])
	{
		tmp = ft_strjoin(exec_paths[i], "/");
		abs_path = ft_strjoin(tmp, cmd);
		free(tmp);
		ret = open(abs_path, O_RDONLY);
		if (ret > 0)
		{
			close(ret);
			free_the_nipples(exec_paths);
			return (abs_path);
		}
		close(ret);
		free(abs_path);
	}
	free_the_nipples(exec_paths);
	return (NULL);
}

char	*get_abs_path(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	*path;
	char	*cmd_path;
	int		ret;

	i = -1;
	cmd_path = NULL;
	ret = open(cmd, O_RDONLY);
	if (ret > 0)
	{
		close(ret);
		return (cmd);
	}
	else
	{
		while (envp[++i])
		{
			tmp = ft_substr(envp[i], 0, c_finder(envp[i], '='));
			if (ft_strcmp(tmp, "PATH"))
			{
				path = ft_substr(envp[i], c_finder(envp[i], '=') + 1,
						ft_strlen(envp[i]));
				cmd_path = find_path(path, cmd);
				free(path);
				free(tmp);
				close(ret);
				return (cmd_path);
			}
			free(cmd_path);
			free(tmp);
		}
		close(ret);
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd[2];
	char	*infile;
	char	*outfile;

	if (argc != 5)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	infile = ft_strdup(argv[1]);
	outfile = ft_strdup(argv[4]);
	cmd[0].cmd_w_args = ft_split(argv[2], ' ');
	cmd[0].cmd_abs_path = get_abs_path(cmd[0].cmd_w_args[0], envp);
	cmd[1].cmd_w_args = ft_split(argv[3], ' ');
	cmd[1].cmd_abs_path = get_abs_path(cmd[1].cmd_w_args[0], envp);
	if (cmd[0].cmd_abs_path == NULL)
	{
		printf("bash: %s: command 1 not found\n", cmd[0].cmd_w_args[0]);
		return (1);
	}
	if (cmd[1].cmd_abs_path == NULL)
	{
		printf("bash: %s: command 2 not found\n", cmd[1].cmd_w_args[0]);
		return (1);
	}
	execute_it(cmd, infile, outfile, envp);
	return (0);
}
