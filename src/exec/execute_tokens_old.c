/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 09:41:22 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/10 14:04:53 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "../builtin/builtin.h"

char		*concat_command_path(char *path, char *command)
{
	char	*ret;
	int		len;

	ret = NULL;
	len = ft_strlen(path) + ft_strlen(command) + 1;
	if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_bzero(ret, len);
	ft_strcat(ret, path);
	ft_strcat(ret, "/");
	ft_strcat(ret, command);
	return (ret);
}

char		*find_command_path(char **path, char *command)
{
	char			*ret;
	DIR				*od;
	struct dirent	*fl;
	int				i;

	i = -1;
	ret = NULL;
	while (path[++i])
	{
		if ((od = opendir(path[i])))
		{
			while ((fl = readdir(od)))
			{
				if (ft_strcmp(command, fl->d_name) == 0)
				{
					closedir(od);
					return (concat_command_path(path[i], command));
				}
			}
			closedir(od);
		}
	}
	return (ret);
}

char		*check_path_bin(char *path, t_sh *sh)
{
	if (access(path, X_OK) != -1)
		return (ft_strdup(path));
	ft_putstr_fd("21sh: no such file or directory: ", 2);
	ft_putendl_fd(path, 2);
	sh->retval = 127;
	return (NULL);
}

char		*command_path(t_env **env, char *command, t_sh *sh)
{
	char	*path;
	char	*ret;
	char	**split;

	ret = NULL;
	if (command[0] == '/' || command[0] == '.')
		return (check_path_bin(command, sh));
	if ((path = get_specific_env("PATH=", env)))
	{
		if ((split = ft_strsplit(path, ':')))
		{
			ret = find_command_path(split, command);
			env_free(split);
		}
		free(path);
	}
	if (!ret)
	{
		ft_putstr_fd("21sh: command not found: ", 2);
		ft_putendl_fd(command, 2);
		sh->retval = 127;
	}
	return (ret);
}

void		free_char_array(char **array)
{
	int		i;

	i = -1;
	if (array)
	{
		while (array[++i])
			free(array[i]);
		if (array)
			free(array);
		array = NULL;
	}
}
