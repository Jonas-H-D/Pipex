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

typedef struct s_struc
{
    char        **args;
    char        *path;
    int         pipId[2];
    int         fdin;
    int         fdout;
    pid_t       child1;
    pid_t       child2;
}   t_struc;

char    *ft_dup(char *str, int i);
char    **ft_split(char *cmd, char sep);
int     ft_strcmp(char *str, int len, char *env);
int     ft_strlen(char *s);
char    *ft_join(char *s1, char *s2);
char    *ft_get_path(char *cmd, char **env);

# endif