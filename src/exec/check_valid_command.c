/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 02:01:21 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/05 12:53:06 by drecours         ###   ########.fr       */
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

char		*existing_command(char **command, t_env **env, t_sh *sh, int fg)
{
	char	*path;
	char	*exec_path;
	char	**path_list;
	int		i;
	int		(*builtin_ptr)(char **, t_sh *);

	(void)sh;
	i = -1;
	path_list = NULL;
	exec_path = NULL;
	if (fg == 2 && (exec_path = get_hash_path(&sh->hash, command[0], sh)))
		return (exec_path);
	if (fg == 1 && (builtin_ptr = get_builtin_function(command[0])))
	{
		sh->retval = builtin_ptr(command, sh);
		return ("ok");
	}
	if ((path = get_specific_env("PATH=", env)))
	{
		if ((path_list = ft_strsplit(path, ':')))
		{
			while (path_list[++i])
				if ((exec_path = found_exec_path(path_list[i], command[0])))
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
