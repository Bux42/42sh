/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 20:23:08 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/19 20:35:18 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		insert_completion(t_sh *sh, t_inp **inp)
{
	t_inp	*cp;
	int		i;

	if (sh->comp_remain && ft_strlen(sh->comp_remain) > 0)
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
	}
}

char		*get_left_word(t_inp *cp)
{
	char	*ret;
	int		i;

	i = 1;
	while (cp->previous && !is_space(cp->previous->c))
	{
		i++;
		cp = cp->previous;
	}
	if (!(ret = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ret[i] = '\0';
	i = 0;
	while (cp && !is_space(cp->c))
	{
		ret[i++] = cp->c;
		cp = cp->next;
	}
	return (ret);
}

void		print_completion(t_sh *sh)
{
	DIR				*od;
	struct dirent	*fl;
	int				dec;
	int				decp;

	if (!(od = opendir("./")))
		return ;
	while ((fl = readdir(od)))
	{
		if (ft_strncmp(sh->comp_debug, fl->d_name, ft_strlen(sh->comp_debug)) == 0)
		{
			write(1, "\e[2m", 5);
			dec = ft_strlen(sh->comp_debug);
			decp = 0;
			if (sh->comp_remain)
			{
				free(sh->comp_remain);
				sh->comp_remain = NULL;
			}
			while (fl->d_name[dec])
			{
				ft_putchar(fl->d_name[dec]);
				check_endline(sh);
				dec++;
				decp++;
			}
			if (decp)
				sh->comp_remain = ft_strdup(&fl->d_name[ft_strlen(sh->comp_debug)]);
			while (decp--)
				custom_left(sh);
			write(1, "\x1b[0m", 5);
			return ;
		}
	}
	dec = ft_strlen(sh->comp_remain);
	decp = dec;
	while (dec--)
	{
		ft_putchar(' ');
		check_endline(sh);
	}
	while (decp--)
		custom_left(sh);
	free(sh->comp_remain);
	sh->comp_remain = NULL;
}

void		autocompletion(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

	sh->posy++;
	sh->posy--;
	if ((cp = get_to_pos(inp)))
	{
		if (!cp->next || is_space(cp->next->c))
		{
			if (!is_space(cp->c))
			{
				if (sh->comp_debug)
				{
					free(sh->comp_debug);
					sh->comp_debug = NULL;
				}
				if ((sh->comp_debug = get_left_word(cp)))
					print_completion(sh);
			}
		}
	}
}
