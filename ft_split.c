/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:27:31 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/09 18:14:05 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	c_w(char const *str, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
		{
			i++;
		}
		if (str[i] != c && str[i] != '\0')
			j++;
		while (str[i] != c && (str[i] != '\0'))
			i++;
	}
	return (j);
}

static char	**freethenipples(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static int	s_p(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	return (i);
}

static int	len_str(char const *s, int i, char c)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**cpy;
	int		k;
	int		i;
	t_plit	ugh;

	init(&k, &i);
	cpy = (char **)malloc(sizeof(char *) * (c_w(s, c) + 1));
	if (!s || !cpy)
		return (0);
	while (s[i])
	{
		ugh.len = 0;
		i += s_p(&s[i], c);
		ugh.start = i;
		ugh.len = len_str(s, i, c);
		i += ugh.len;
		if (ugh.len)
		{
			cpy[++k] = ft_substr(s, ugh.start, ugh.len);
			if (!(cpy[k]))
				return (freethenipples(cpy));
		}
	}
	cpy[++k] = 0;
	return (cpy);
}
