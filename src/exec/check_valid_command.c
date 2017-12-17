/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 02:01:21 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/17 12:57:35 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char		*found_exec_path(char *path, char *command)
{
	char			*full_path;
	DIR				*od;
	struct dirent	*fl;
	int				len;

	full_path = NULL;
	len = 0;
	if ((od = opendir(path)))
	{
		while ((fl = readdir(od)))
			if (ft_strcmp(command, fl->d_name) == 0 && ++len)
				break ;
		closedir(od);
		if (!len)
			return (NULL);
		len += ft_strlen(command);
		len += ft_strlen(path);
		if (!(full_path = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		ft_bzero(full_path, len);
		ft_strcat(full_path, path);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, command);
	}
	return (full_path);
}

char		*check_exec_path(char *command, t_env **env, int rep)
{
	char	*home;
	int		len;
	char	*tmp;

	len = 0;
	if (command[0] == '~' && command[1] == '/')
	{
		if ((home = get_specific_env("HOME=", env)))
		{
			len += ft_strlen(home);
			len += ft_strlen(&command[1]);
			if (!(tmp = (char*)malloc(sizeof(char) * (len + 1))))
				return (NULL);
			ft_bzero(tmp, len);
			ft_strcat(tmp, home);
			free(home);
			ft_strcat(tmp, &command[1]);
			if (rep)
				free(command);
			return (tmp);
		}
	}
	return (command);
}

char		*existing_command(char *command, t_env **env)
{
	char	*path;
	char	*exec_path;
	char	**path_list;
	int		i;

	i = -1;
	path_list = NULL;
	exec_path = NULL;
	if (command[0] == '/')
		return (ft_strdup(command));
	if (ft_strcmp(command, "cd") == 0)
		return (ft_strdup(command));
	if (ft_strcmp(command, "env") == 0)
		return (ft_strdup(command));
	if (ft_strcmp(command, "setenv") == 0)
		return (ft_strdup(command));
	if (ft_strcmp(command, "unsetenv") == 0)
		return (ft_strdup(command));
	if ((path = get_specific_env("PATH=", env)))
	{
		if ((path_list = ft_strsplit(path, ':')))
		{
			while (path_list[++i])
				if ((exec_path = found_exec_path(path_list[i], command)))
					break ;
			i = -1;
			while (path_list[++i])
				free(path_list[i]);
			free(path_list);
			free(path);
		}
	}
	return (exec_path);
}
