/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 02:01:21 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/15 04:52:29 by videsvau         ###   ########.fr       */
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
		closedir(od);
		ft_putstr(full_path);
	}
	return (full_path);
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
	if (command[0] == '/' || command[1] == '/')
		;
	else if ((path = get_specific_env("PATH=" ,env)))
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
		}
	}
	return (exec_path);
}
