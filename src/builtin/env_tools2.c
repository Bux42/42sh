/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 14:42:12 by drecours          #+#    #+#             */
/*   Updated: 2018/04/05 13:18:40 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

t_env				*tab_in_env(char **tab)
{
	t_env	*env;
	t_env	*first;
	int		i;

	i = 0;
	first = NULL;
	if (tab[0])
		first = new_env(tab[0]);
	env = first;
	while (tab[i])
	{
		env->next = new_env(tab[i]);
		i++;
		env = env->next;
	}
	return (first);
}

void				show_args(char **exec)
{
	int		i;
	char	*j;

	i = 0;
	ft_putstr_fd("#env executing: ", STDERR_FILENO);
	ft_putendl_fd(exec[i], STDERR_FILENO);
	while (exec[i])
	{
		ft_putstr_fd("#env    arg[", STDERR_FILENO);
		j = ft_itoa(i);
		ft_putstri_fd(j, STDERR_FILENO);
		free(j);
		ft_putstr_fd("]= '", STDERR_FILENO);
		ft_putstr_fd(exec[i], STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		i++;
	}
}

int					erase_file(char *new_path, t_sh *sh)
{
	if ((sh->fd = open(new_path, O_TRUNC | O_RDWR, 0777)) == -1)
	{
		ft_putendl_fd("Couldn't open .history correctly", 2);
		free(new_path);
		return (12);
	}
	if (close(sh->fd))
	{
		ft_putendl_fd("Could'nt close .history correctly.", 2);
		sh->fd = 0;
		free(new_path);
		return (11);
	}
	return (0);
}

int					change_fd(t_sh *sh, char *path)
{
	char	*new_path;
	int		err;

	new_path = ft_strjoin(path, "/.history");
	if (close(sh->fd))
	{
		ft_putendl_fd("Couldn't close .history correctly.", 2);
		sh->fd = -1;
		free(new_path);
		return (11);
	}
	if ((err = erase_file(new_path, sh)))
		return (err);
	if ((sh->fd = open(new_path, O_CREAT | O_RDWR, 0777)) == -1)
	{
		ft_putendl_fd("Couldn't open .history correctly", 2);
		free(new_path);
		return (12);
	}
	free(new_path);
	return (0);
}

int					erase_fg(char *fg, int i)
{
	free(fg);
	if (i == 4)
		return (show_err(4, '0', NULL));
	return (i);
}
