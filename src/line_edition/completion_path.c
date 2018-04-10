/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 01:45:42 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/10 13:16:57 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		completion_readdir(DIR *od, t_sh *sh, t_inp *cp)
{
	struct dirent	*fl;

	while ((fl = readdir(od)))
	{
		if (ft_strncmp(sh->comp_debug, fl->d_name,
					ft_strlen(sh->comp_debug)) == 0)
		{
			if (sh->comp_remain)
				delete_remain(sh, sh->comp_remain);
			found(sh, od, fl, cp);
			if (sh->comp_remain == NULL)
				closedir(od);
			return ;
		}
	}
	if (sh->comp_remain)
		not_found(sh, cp);
	closedir(od);
}

void		fill_path(char *ret, char *home, int len, t_inp *cp)
{
	int		i;

	i = 0;
	if (home)
	{
		cp = cp->next;
		while (i < (int)ft_strlen(home))
		{
			ret[i] = home[i];
			i++;
		}
		free(home);
		home = NULL;
	}
	while (i < len)
	{
		ret[i++] = cp->c;
		if (cp->next)
			cp = cp->next;
		else
			break ;
	}
}

char		*get_comp_path(t_sh *sh, t_inp *cp)
{
	char	*ret;
	char	*home;
	int		len;

	len = 0;
	home = NULL;
	while (cp)
	{
		if (cp->c == '~')
			if (cp->next && cp->next->c == '/')
				if ((home = get_specific_env("HOME=", &sh->env)))
					len += ft_strlen(home) - 2;
		if (cp->c == '~')
			break ;
		if (!cp->previous || is_space(cp->previous->c))
			break ;
		len++;
		cp = cp->previous;
	}
	if (!(ret = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ret[len] = '\0';
	fill_path(ret, home, len, cp);
	return (ret);
}
