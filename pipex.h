#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1

char	**ft_split(char *str, char sep);
char    *ft_path(char *cmd, char **env);
int     ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s1, int n);
int	    ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
int 	ft_strichr(char *s, char c);
void    ft_exec(char *cmd, char **env);

# endif