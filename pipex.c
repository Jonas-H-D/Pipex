/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:35:46 by jhermon-          #+#    #+#             */
/*   Updated: 2022/02/09 11:25:25 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	openfile(char *file, int mode)
{
	if (mode == 0)
	{
		if (access(file, F_OK))
		{
			write(STDERR, "pipex: ", 7);
			write(STDERR, "No such file or directory: ", 28);
			write(STDERR, file, ft_strlen(file));
			write(STDERR, "\n", 1);
			return (STDIN);
		}
		return (open(file, O_RDONLY));
	}
	else
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}

void	ft_child1(t_struc *struc, char **argv, char **env)
{
	dup2(struc->fdin, STDIN);
	dup2(struc->pipid[1], STDOUT);
	close(struc->pipid[0]);
	close(struc->pipid[1]);
	struc->args = ft_split(argv[2], ' ');
	struc->path = ft_get_path(struc, struc->args[0], env);
	execve(struc->path, struc->args, env);
	write(STDERR, "pipex: ", 7);
	write(STDERR, "command not found:  ", 20);
	write(STDERR, struc->path, ft_strlen(struc->path));
	write(STDERR, "\n", 1);
}

void	ft_child2(t_struc *struc, char **argv, char **env)
{
	dup2(struc->fdout, STDOUT);
	dup2(struc->pipid[0], STDIN);
	close(struc->pipid[1]);
	close(struc->pipid[0]);
	struc->args = ft_split(argv[3], ' ');
	struc->path = ft_get_path(struc, struc->args[0], env);
	execve(struc->path, struc->args, env);
	write(STDERR, "pipex: ", 7);
	write(STDERR, "command not found:  ", 20);
	write(STDERR, struc->path, ft_strlen(struc->path));
	write(STDERR, "\n", 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_struc	struc;

	if (argc == 5)
	{
		struc.fdin = openfile(argv[1], 0);
		struc.fdout = openfile(argv[4], 1);
		pipe(struc.pipid);
		struc.child1 = fork();
		if (struc.child1 == 0)
			ft_child1(&struc, argv, envp);
		struc.child2 = fork();
		if (struc.child2 == 0)
			ft_child2(&struc, argv, envp);
		close(struc.pipid[0]);
		close(struc.pipid[1]);
		waitpid(struc.child1, NULL, 0);
		waitpid(struc.child1, NULL, 0);
	}
	else
		write(STDERR, "Invalid number of arguments.\n", 29);
	return (1);
}
