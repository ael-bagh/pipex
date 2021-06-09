/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:32:59 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/09 15:33:31 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
