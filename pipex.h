/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:39:02 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/09 19:01:02 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_cmd
{
	char	**cmd_w_args;
	char	*cmd_abs_path;
}				t_cmd;

typedef struct s_plit
{
	int	start;
	int	len;
}
				t_plit;

void		init(int *k, int *i);
char		*ft_strdup(const char *s1);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
void		free_the_nipples(char **s);
void		execute_it(t_cmd cmd[2], char *infile, char *outfile, char **envp);
int			c_finder(const char *str, char c);
int			ft_strcmp(const char *str1, const char *str2);
int			arg_error(t_cmd cmd[2]);

#endif