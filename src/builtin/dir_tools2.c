/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:50:02 by drecours          #+#    #+#             */
/*   Updated: 2018/01/29 14:50:43 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

size_t		path_subcpy(const char *source, char *dest,
		size_t start, size_t len)
{
	size_t		i;

	i = start;
	while (i < start + len)
	{
		dest[i - start] = source[i];
		++i;
	}
	dest[i - start] = '\0';
	return (i - start);
}

size_t		path_trim(char *path, size_t size)
{
	char	*trimmed_str;
	size_t	len;

	trimmed_str = ft_strtrim(path);
	if (trimmed_str == NULL)
		return (0);
	len = ft_strlen(trimmed_str);
	path_subcpy(trimmed_str, path, 0, len < size ? len : size);
	free(trimmed_str);
	return (len);
}

char	*find_man_path(char *relative)
{
	char	buff[2048];
	char	*path;
	char	*tmp;
	int		i;

	getwd(buff);
	path = ft_strjoin(getwd(buff), "/");
	tmp = ft_strjoin(path, relative);
	free(path);
	path_eval(tmp);
	path = ft_strjoin(tmp, "man/");
	free(tmp);
	i = ft_strlen(path);
	path[i - 5] = '/';
	path[i - 6] = 'c';
	path[i - 7] = 'r';
	path[i - 8] = 's';
	return (path);
}
