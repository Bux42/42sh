/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 10:22:54 by hlely             #+#    #+#             */
/*   Updated: 2018/03/08 19:55:21 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"

static t_int	*newint(int i)
{
	t_int	*list;

	CHECKMC(list = (t_int*)malloc(sizeof(t_int)));
	list->index = i;
	list->next = NULL;
	return (list);
}

static void		addindex(t_int **list, int i)
{
	t_int	*begin;
	t_int	*new;

	new = newint(i);
	if (*list == NULL)
		*list = new;
	else
	{
		begin = *list;
		LISTNEXT((*list));
		(*list)->next = new;
		*list = begin;
	}
}

static int		get_len(char *pwd)
{
	int		i;
	t_int	*list;
	t_int	*begin;

	i = 0;
	list = NULL;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			addindex(&list, i);
		i++;
	}
	begin = list;
	LISTNEXT(list);
	i = list->index;
	while (begin)
	{
		list = begin;
		begin = begin->next;
		free(list);
	}
	return (i);
}

void			normalize_pwd(char ***environ, int i)
{
	int		j;
	char	*pwd;
	char	*newpwd;
	char	*dot;

	CHECKMCVOID(pwd = ft_getenv(*environ, "PWD"));
	while ((dot = ft_strdup(ft_strstr(pwd, ".."))))
	{
		newpwd = ft_strsub(pwd, 0, ft_strlen(pwd) - ft_strlen(dot));
		j = get_len(newpwd);
		j = (j) ? j : j + 1;
		newpwd = ft_strsubdel(newpwd, 0, j);
		while (dot[i] && dot[i] != '/')
			i++;
		ft_strdel(&pwd);
		pwd = ft_strjoin(newpwd, dot + i);
		ft_strdel(&newpwd);
		ft_strdel(&dot);
	}
	if (ft_strlen(pwd) > 1 && pwd[ft_strlen(pwd) - 1] == '/')
		pwd[ft_strlen(pwd) - 1] = '\0';
	ft_setenv("PWD", pwd, environ);
	ft_strdel(&pwd);
}
