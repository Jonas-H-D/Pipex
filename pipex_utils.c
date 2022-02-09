/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:28:48 by jhermon-          #+#    #+#             */
/*   Updated: 2022/02/09 11:44:28 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_dup(char *str, int i)
{
	char	*dest;
	int		j;

	dest = (char *)malloc(sizeof (char) * i + 1);
	j = 0;
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	**ft_split(char *cmd, char sep)
{
	char	**ret;
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == sep)
			count++;
		i++;
	}
	ret = malloc(sizeof(char *) * (count + 2));
	if (!ret)
		return (NULL);
	ret[count + 1] = NULL;
	j = 0;
	while (j < count + 1)
	{
		i = 0;
		while (cmd[i] && cmd[i] != sep)
			i++;
		ret[j] = ft_dup(cmd, i);
		j++;
		cmd = cmd + i + 1;
	}
	return (ret);
}

int	ft_strcmp(char *str, int len, char *env)
{
	while (--len > 0 && *str && *env && *env == *str)
	{
		env++;
		str++;
	}
	return (*env - *str);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_join(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i++] = '\0';
	return (dest);
}

char	*ft_get_path(t_struc *struc, char *cmd, char **env)
{
	char	*bin;
	char	*dir;
	int		i;
	int		j;

	while (*env && ft_strcmp("PATH=", 5, *env) != 0)
		env++;
	struc->getpath = *env + 5;
	i = 0;
	while (struc->getpath[i])
	{
		bin = malloc(sizeof(char) * ft_strlen(struc->getpath));
		j = 0;
		i = 0;
		while (struc->getpath[i] && struc->getpath[i] != ':')
			bin[j++] = struc->getpath[i++];
		bin[j++] = '/';
		dir = ft_join(bin, cmd);
		if (access(dir, F_OK) == 0)
			return (dir);
		free(bin);
		dir = NULL;
		struc->getpath += i + 1;
	}
	return (cmd);
}
