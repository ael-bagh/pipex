/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:32:59 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/09 19:01:15 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	arg_error(t_cmd cmd[2])
{
	if (cmd[1].cmd_abs_path == NULL && cmd[0].cmd_abs_path == NULL)
	{
		printf("bash: %s: command not found\n", cmd[0].cmd_w_args[0]);
		printf("bash: %s: command not found\n", cmd[1].cmd_w_args[0]);
		return (1);
	}
	if (cmd[0].cmd_abs_path == NULL)
	{
		printf("bash: %s: command not found\n", cmd[0].cmd_w_args[0]);
		return (1);
	}
	if (cmd[1].cmd_abs_path == NULL)
	{
		printf("bash: %s: command not found\n", cmd[1].cmd_w_args[0]);
		return (1);
	}
	return (0);
}

void	free_the_nipples(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i])
			free(s[i]);
		i++;
	}
	free(s);
}

void	free_all(t_cmd *cmd, char *input, char *output)
{
	free(output);
	free(input);
	free(cmd[0].cmd_abs_path);
	free(cmd[1].cmd_abs_path);
}

int	c_finder(const char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (0);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = -1;
	while (str1[++i])
	{
		if (str1[i] != str2[i])
			return (0);
	}
	return (1);
}
