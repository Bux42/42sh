/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:17:29 by drecours          #+#    #+#             */
/*   Updated: 2018/03/19 14:56:06 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

static char		*storage_path(char *path, char *name)
{
	size_t	end;
	char	*path_file;
	char	*tmp;

	path_file = NULL;
	if (!path || !name)
		return (NULL);
	end = (ft_strlen(path) - 1);
	if (path[end] == '/')
		path_file = ft_strjoin(path, name);
	else
	{
		if ((tmp = ft_strjoin(path, "/")))
		{
			path_file = ft_strjoin(tmp, name);
			ft_strdel(&tmp);
		}
	}
	return (path_file);
}

static t_hash	*add_new_node(char *bin, char *path)
{
	t_hash	*new_node;

	if (!(new_node = (t_hash *)ft_memalloc(sizeof(t_hash))))
		return (NULL);
	new_node->bin = ((bin != NULL) ? ft_strdup(bin) : NULL);
	new_node->path = ((path != NULL) ? ft_strdup(path) : NULL);
	new_node->next = NULL;
	return (new_node);
}

static void		get_dir_elem(t_hash **addr, DIR *directory, char *path)
{
	t_hash			*new_node;
	struct dirent	*elem;
	char			*new_path;
	struct stat		st;

	while ((elem = readdir(directory)) != NULL)
	{
		if (elem->d_name[0] == '.')
			continue ;
		if (!(new_path = storage_path(path, elem->d_name)))
			return ;
		if ((stat(new_path, &st)) == 0)
			if (((access(new_path, X_OK)) == 0) && (S_ISREG(st.st_mode)))
			{
				if (!(new_node = add_new_node(elem->d_name, new_path)))
					return ;
				new_node->next = *addr;
				*addr = new_node;
			}
		ft_strdel(&(new_path));
	}
}

void		ft_tabdel(char **t)
{
	int		i;

	i = -1;
	if (t != NULL)
	{
		while (t[++i] != NULL)
			ft_strdel(&(t[i]));
		free((char **)t);
		t = NULL;
	}
}

void			init_bin_list(t_hash **addr, char *path)
{
	char		**all_path;
	int			i;
	struct stat	st;
	DIR			*directory;

	if ((all_path = ft_strsplit(path, ':')) == NULL)
		return ;
	i = (-1);
	while (all_path[++i] != NULL)
		if ((access(all_path[i], F_OK)) == 0)
			if ((stat(all_path[i], &st)) == 0)
				if ((S_ISDIR(st.st_mode)))
					if ((access(all_path[i], X_OK)) == 0)
						if ((directory = opendir(all_path[i])) != NULL)
						{
							get_dir_elem(addr, directory, all_path[i]);
							closedir(directory);
						}
	ft_tabdel(all_path);
}
