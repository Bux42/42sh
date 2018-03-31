/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_builtin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 20:59:04 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/31 23:30:20 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		get_bin(t_env **env, t_sh *sh)
{
	char			**split;
	char			*path;
	DIR				*od;
	struct dirent	*fl;
	int				i;

	i = -1;
	if ((path = get_specific_env("PATH=", env)))
	{
		if ((split = ft_strsplit(path, ':')))
		{
			while (split[++i])
			{
				if ((od = opendir(split[i])))
				{
					while ((fl = readdir(od)))
						if (fl->d_name[0] != '.')
							bin_push_front(&sh->bin, fl->d_name);
					closedir(od);
				}
			}
			free_char_array(split);
		}
		free(path);
	}
}

int			is_separator(char c)
{
	if (c == '|')
		return (1);
	if (c == '&')
		return (1);
	if (c == ';')
		return (1);
	return (0);
}

int			complete_builtin(t_inp **inp)
{
	t_inp	*cp;

	cp = *inp;
	while (cp->previous)
	{
		if (cp->previous->c == ' ')
			break ;
		cp = cp->previous;
	}
	if (cp->previous)
	{
		while (cp->previous && cp->previous->c == ' ')
			cp = cp->previous;
		if (cp->previous && !is_separator(cp->previous->c))
			return (0);
	}
	return (1);
}

void		found_bin(t_sh *sh, char *name, t_inp *cp)
{
	sh->over = get_diff(name, sh);
	if (ft_strlen(sh->comp_debug) == ft_strlen(name))
		return ((void)free_comp(3, sh));
	write(1, "\e[2m", 5);
	free_comp(1, sh);
	sh->comp_remain = ft_strdup(&name[ft_strlen(sh->comp_debug)]);
	while (sh->comp_remain[++sh->dec])
	{
		ft_putchar(sh->comp_remain[sh->dec]);
		check_endline(sh);
	}
	write(1, "\x1b[0m", 5);
	while (cp)
	{
		sh->dec++;
		ft_putchar(cp->c);
		check_endline(sh);
		cp = cp->next;
	}
	print_spaces(sh->over, sh);
	sh->dec += sh->over;
	while (sh->dec--)
		custom_left(sh);
}

void		print_completion_builtin(t_sh *sh, t_inp *cp, t_bin **bin)
{
	t_bin	*bincp;

	if ((bincp = (*bin)))
	{
		while (bincp)
		{
			if (ft_strncmp(sh->comp_debug, bincp->name, ft_strlen(sh->comp_debug)) == 0)
			{
				if (sh->comp_remain)
					delete_remain(sh, sh->comp_remain);
				found_bin(sh, bincp->name, cp);
				return ;
			}
			bincp = bincp->next;
		}
	}
	if (sh->comp_remain)
		not_found(sh, cp);
}
