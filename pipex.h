/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:20:34 by jhermon-          #+#    #+#             */
/*   Updated: 2022/02/09 11:45:20 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_struc
{
	char	**args;
	char	*getpath;
	char	*path;
	int		pipid[2];
	int		fdin;
	int		fdout;
	pid_t	child1;
	pid_t	child2;
}	t_struc;

char	*ft_dup(char *str, int i);
char	**ft_split(char *cmd, char sep);
int		ft_strcmp(char *str, int len, char *env);
int		ft_strlen(char *s);
int		ft_linecount(char *cmd, char sep);
char	*ft_join(char *s1, char *s2);
char	*ft_get_path(t_struc *struc, char *cmd, char **env);
void	ft_child1(t_struc *struc, char **argv, char **env);
void	ft_child2(t_struc *struc, char **argv, char **env);

#endif
