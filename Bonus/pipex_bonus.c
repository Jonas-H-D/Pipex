#include "pipex.h"
/*void    init_child_tab(int  t)
{
    int 
    if (t < 6)
        exit(2);
    
}*/
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

void    ft_childx(t_struc *struc, char **argv, char **env)
{
    struc->childx = fork();
    if (!struc->childx)
    {
        if (struc->pos == 0)
    dup2(struc->pipId[0], STDIN);
    close(struc->pipId[1]);
    close(struc->pipId[0]);
    struc->args = ft_split(argv[pos], ' ');
    struc->path = ft_get_path(struc->args[0], env);
    printf("path[%d] = %s\n", pos, struc->path);
    execve(struc->path, struc->args, env);
}

void	creat_pipes(t_struc *struc)
{
	int	i;

	i = 0;
	while (i < struc->cmd_nbr - 1)
	{
		pipe(struc->pipe + 2 * i);
		i++;
	}
}

// try multi pipes file1 "ls -l" "sort" "uniq" "wc -l" file4

int main(int argc, char **argv, char **envp)
{
    t_struc struc;

    if (argc >= 5)
    {
        struc.fdin = open(argv[1], O_RDONLY);
        struc.fdout = open(argv[argc], O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        struc.cmd_nbr = argc - 3;
        struc.pipe_nbr = 2 * (struc.cmd_nbr - 1);
        struc.pipe = (int *)malloc(sizeof(int) * struc.pipe_nbr);
        if (!struc.pipe)
            return(-1);
        creat_pipes(&struc);
        struc.pos = 0;
        while(struc.pos < struc.cmd_nbr)
        {
            ft_childx(&struc, argv, envp);
            struc.pos++;
        }
        }
        close(struc.pipId[0]);
        close(struc.pipId[1]);
        //waitpid(struc.child1, NULL, 0);
        waitpid(-1, NULL, 0);
        //waitpid(struc.child1, NULL, 0);
    }
    else 
        perror ("Wrong number of arguments \n");
    return (0);
}