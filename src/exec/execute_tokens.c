/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 09:41:22 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/13 18:28:29 by videsvau         ###   ########.fr       */
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

char		*command_path(t_env **env, char *command)
{
	char	*path;
	char	*ret;
	char	**split;

	ret = NULL;
	if ((path = get_specific_env("PATH=", env)))
	{
		if ((split = ft_strsplit(path, ':')))
		{
			ret = find_command_path(split, command);
		}
	}
	else
		return (NULL);
	return (ret);
}
