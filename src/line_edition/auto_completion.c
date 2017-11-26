/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 20:23:08 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/26 01:03:55 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		insert_completion(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		i;

	if (sh->comp_remain)
	{
		if ((cp = get_to_pos(inp)))
		{
			i = -1;
			while (sh->comp_remain[++i])
			{
				inp_insert_posat(&sh->inpl->inp, sh->comp_remain[i]);
				ft_putchar(sh->comp_remain[i]);
				check_endline(sh);
				overwrite_remaining(sh, &sh->inpl->inp);
			}
		}
		free_comp(3, sh);
	}
}

char		*get_comp_path(t_sh *sh, t_inp *cp)
{
	char	*ret;
	char	*home;
	int		len;
	int		i;

	len = 0;
	i = 0;
	home = NULL;
	while (cp)
	{
		if (cp->c == '~')
		{
			if (cp->next && cp->next->c == '/')
			{
				if ((home = get_specific_env("HOME=", &sh->env)))
					len += ft_strlen(home) - 2;
			}
		}
		if (!cp->previous || is_space(cp->previous->c))
			break ;
		len++;
		cp = cp->previous;
	}
	if (!(ret = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ret[len] = '\0';
	if (home)
	{
		cp = cp->next;
		while (i < (int)ft_strlen(home))
		{
			ret[i] = home[i];
			i++;
		}
	}
	while (i < len)
	{
		ret[i++] = cp->c;
		if (cp->next)
			cp = cp->next;
		else
			break ;
	}
	return (ret);
}

char		*get_left_word(t_inp *cp, t_sh *sh)
{
	char	*ret;
	int		i;
	int		slash;

	i = 1;
	slash = 0;
	free_comp(6, sh);
	while (cp->previous && !is_space(cp->previous->c))
	{
		if (cp->previous->c == '/' && (slash++) > -1)
			break ;
		i++;
		cp = cp->previous;
	}
	if (!(ret = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (slash)
		sh->comp_path = get_comp_path(sh, cp);
	else
		sh->comp_path = ft_strdup("./");
	ret[i] = '\0';
	i = 0;
	while (cp && !is_space(cp->c))
	{
		ret[i++] = cp->c;
		cp = cp->next;
	}
	return (ret);
}

int			get_diff(char *fl, t_sh *sh)
{
	int		new_len;
	int		ret;

	new_len = ft_strlen(sh->comp_debug);
	new_len += ft_strlen(&fl[ft_strlen(sh->comp_debug)]);
	if (new_len < sh->old_len)
	{
		ret = sh->old_len;
		sh->old_len = new_len;
		return (ret - new_len);
	}
	else
		sh->old_len = new_len;
	return (0);
}

void		print_completion(t_sh *sh, t_inp **inp)
{
	DIR				*od;
	struct dirent	*fl;
	int				dec;
	int				ret;
	int				over;
	t_inp			*cp;

	cp = get_to_pos(inp);
	cp = cp->next;
	dec = -1;
	over = 0;
	if (!(od = opendir(sh->comp_path)))
		return ;
	while ((fl = readdir(od)))
	{
		if (ft_strncmp(sh->comp_debug, fl->d_name, ft_strlen(sh->comp_debug)) == 0)
		{
			over = get_diff(fl->d_name, sh);
			if (ft_strlen(sh->comp_debug) == ft_strlen(fl->d_name))
			{
				free_comp(3, sh);
				return ;
			}
			write(1, "\e[2m", 5);
			sh->comp_remain = ft_strdup(&fl->d_name[ft_strlen(sh->comp_debug)]);
			while (sh->comp_remain[++dec])
			{
				ft_putchar(sh->comp_remain[dec]);
				check_endline(sh);
			}
			write(1, "\x1b[0m", 5);
			while (cp)
			{
				dec++;
				ft_putchar(cp->c);
				check_endline(sh);
				cp = cp->next;
			}
			print_spaces(over, sh);
			dec += over;
			while (dec--)
				custom_left(sh);
			closedir(od);
			return ;
		}
	}
	if (sh->comp_remain)
	{
		dec = ft_strlen(sh->comp_remain) - 1;
		dec += inp_list_len(&cp);
		ret = dec;
		print_spaces(dec, sh);
		while (ret--)
			custom_left(sh);
		ret = 0;
		while (cp)
		{
			ft_putchar(cp->c);
			check_endline(sh);
			ret++;
			cp = cp->next;
		}
		while (ret--)
			custom_left(sh);
		free_comp(1, sh);
	}
	closedir(od);
}

void		erase_completion(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		dec;

	if (!sh->comp_remain)
		return ;
	dec = 0;
	if ((cp = get_to_pos(inp)))
	{
		while (cp)
		{
			dec++;
			cp = cp->next;
		}
	}
	dec += ft_strlen(sh->comp_remain);
	free_comp(1, sh);
	print_spaces(dec, sh);
	while (dec--)
		custom_left(sh);
	overwrite_remaining(sh, inp);
}

void		autocompletion(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	if ((cp = get_to_pos(inp)) && cp->pos != 2)
	{
		if (!cp->next || is_space(cp->next->c))
		{
			if (!is_space(cp->c))
			{
				if (cp->c != '/')
				{
					if ((sh->comp_debug = get_left_word(cp, sh)))
						print_completion(sh, &sh->inpl->inp);
				}
				else
					free_comp(11, sh);
			}
			else
				free_comp(11, sh);
		}
		else
			free_comp(3, sh);
	}
	else
		rewrite_beginning(sh, cp);
}
