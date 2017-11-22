/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 20:23:08 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/22 19:28:05 by videsvau         ###   ########.fr       */
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
	sh->retval = len;
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

void		print_completion(t_sh *sh)
{
	DIR				*od;
	struct dirent	*fl;
	int				dec;
	int				decp;

	if (!(od = opendir(sh->comp_path)))
		return ;
	//free(sh->comp_path);
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
			write(1, "\x1b[0m", 5);
			overwrite_remaining(sh, &sh->inpl->inp);
			write(1, "\e[2m", 5);
			while (decp--)
				custom_left(sh);
			write(1, "\x1b[0m", 5);
			return ;
		}
	}
	closedir(od);
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

void		erase_completion(t_sh *sh, t_inp **inp)
{
	int		i;
	int		j;
	int		len;
	t_inp	*cp;

	len = 1;
	if ((cp = get_to_pos(inp)))
	{
		while (cp->next)
		{
			cp = cp->next;
			len++;
		}
	}
	if (sh->comp_remain)
	{
		i = ft_strlen(sh->comp_remain) + len;
		j = i;
		while (i--)
		{
			ft_putchar(' ');
			check_endline(sh);
		}
		while (j--)
			custom_left(sh);
		overwrite_remaining(sh, &sh->inpl->inp);
		free(sh->comp_remain);
		sh->comp_remain = NULL;
	}
}

void		autocompletion(t_inp **inp, t_sh *sh)
{
	t_inp	*cp;

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
				if ((sh->comp_debug = get_left_word(cp, sh)))
					print_completion(sh);
			}
			else
				erase_completion(sh, &sh->inpl->inp);
		}
	}
	else
		erase_completion(sh, &sh->inpl->inp);
}
