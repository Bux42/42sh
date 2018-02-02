/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 02:01:15 by videsvau          #+#    #+#             */
/*   Updated: 2018/02/02 18:21:12 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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

void		found(t_sh *sh, DIR *od, struct dirent *fl, t_inp *cp)
{
	sh->over = get_diff(fl->d_name, sh);
	if (ft_strlen(sh->comp_debug) == ft_strlen(fl->d_name))
		return ((void)free_comp(3, sh));
	write(1, "\e[2m", 5);
	free_comp(1, sh);
	sh->comp_remain = ft_strdup(&fl->d_name[ft_strlen(sh->comp_debug)]);
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
	return ((void)closedir(od));
}

void		not_found(t_sh *sh, t_inp *cp)
{
	int		ret;

	sh->dec = ft_strlen(sh->comp_remain) - 1;
	sh->dec += inp_list_len(&cp);
	ret = sh->dec;
	print_spaces(sh->dec, sh);
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
	free_comp(3, sh);
}

void		print_completion(t_sh *sh, t_inp **inp)
{
	DIR				*od;
	struct dirent	*fl;
	t_inp			*cp;

	cp = get_to_pos(inp);
	cp = cp->next;
	sh->dec = -1;
	sh->over = 0;
	if (!(od = opendir(sh->comp_path)))
		return ;
	while ((fl = readdir(od)))
	{
		if (ft_strncmp(sh->comp_debug, fl->d_name, ft_strlen(sh->comp_debug))
				== 0)
		{
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
