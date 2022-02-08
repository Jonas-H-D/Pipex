/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:35:46 by jhermon-          #+#    #+#             */
/*   Updated: 2022/01/20 12:29:56 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void    ft_child1(t_struc *struc, char **argv, char **env)
{
    dup2(struc->fdin, STDIN);
    dup2(struc->pipId[1], STDOUT);
    close(struc->pipId[0]);
    close(struc->pipId[1]);
    struc->args = ft_split(argv[2], ' ');
    struc->path = ft_get_path(struc->args[0], env);
    execve(struc->path, struc->args, env);
}

void    ft_child2(t_struc *struc, char **argv, char **env)
{
    dup2(struc->fdout, STDOUT);
    dup2(struc->pipId[0], STDIN);
    close(struc->pipId[1]);
    close(struc->pipId[0]);
    struc->args = ft_split(argv[3], ' ');
    struc->path = ft_get_path(struc->args[0], env);
    execve(struc->path, struc->args, env);
}

int main(int argc, char **argv, char **envp)
{
    t_struc    struc;

    if (argc == 5)
    {
        struc.fdin = open(argv[1], O_RDONLY);
        struc.fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        pipe(struc.pipId);
        /*if (struc.pipId == -1)
        {
            perror ("Issue with pipe opening: \n");
            return (2);
        }*/
        struc.child1 = fork();
        /*if (struc.child1 < 0)
        {
            perror ("Issue with child1 fork: \n");
            return (2);
        }*/
        if (struc.child1 == 0)
            ft_child1(&struc, argv, envp);
        struc.child2 = fork();
        /*if (struc.child2 < 0)
        {
            perror ("Issue with child2 fork: \n");
            return (2);
        }*/
        if (struc.child2 == 0)
            ft_child2(&struc, argv, envp);
        close(struc.pipId[0]);
        close(struc.pipId[1]);
        waitpid(struc.child1, NULL, 0);
        waitpid(struc.child1, NULL, 0);
    }
    else 
        perror ("Wrong number of arguments \n");
    return (0);
}