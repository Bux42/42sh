/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:11:21 by drecours          #+#    #+#             */
/*   Updated: 2018/03/01 16:22:54 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int		show_err(int err, char c)
{
	if (err == 1)
		ft_putstr_fd("history: Too many arguments.", STDERR_FILENO);
	if (err == 2)
	{
		ft_putstr_fd("history: illegal option -- ", STDERR_FILENO);
		ft_putchar_fd(c, STDERR_FILENO);
		custom_return();
		ft_putstr_fd("usage: history [-nA | -C] [[0]n]", STDERR_FILENO);
	}
	if (err == 3)
		ft_putstr_fd("history: Arguments must be numerical.", STDERR_FILENO);
	if (err == 4)
		ft_putstr_fd("history: -A and -C together is illegal", STDERR_FILENO);
	custom_return();
	return (err);
}

int		put(char c, char *fg)
{
	int			i;

	i = 0;
	if (c == 'A')
		fg[0] = 'A';
	if (c == 'C')
		fg[1] = 'C';
	if (c == 'n')
		fg[2] = 'n';
	return (0);
}

int		built_err(char **exec, char *fg)
{
	int			i;
	int			j;
	const char 	*flag = "ACn";

	i = 0;
	j = 0;
	while (exec[++i])
	{
		if (ft_strcmp("--", exec[i]) == 0)
		{
			if (exec[i + 1] && exec[i + 2] && exec[i + 3])
				return (show_err(1, 'c'));
			return (0);
		}
		if (exec[i][0] == '-')
		{
			while (exec[i][++j])
				if (ft_strchr(flag, exec[i][j]) == NULL || put(exec[i][j], fg))
					return (show_err(2, exec[i][j]));
			j = 0;
		}
		else if (exec[i + 1]  && exec[i + 2])
			return (show_err(1, '0'));
		else
			return (0);
	}
	return (0);
}

int		builtin_hist(int i, t_his **hist, int lg, char *fg)
{
	int		len;
	int		max;
	int		pos;
	t_inp	*cp;
	t_his	*new;

	len = 0;
	new = *hist;
	pos = (i < 0) ? 1 : 0;
	i = (i < 0) ? -i : i;
	if (fg[1] == 'C')
		return (history_clean(fg[2], hist));
	if (i == 0 || lg == 0)
		return (0);
	while (new->next)
		new = new->next;
	max = history_len(hist);
	while (new->previous)
	{
		if ((len >= i && len < i + lg && pos == 1)
				|| (len >= (max - i) && len < (max - i + lg) && pos == 0))
		{
			if (fg[2] == 'n')
			{
				ft_putnbr(len);
				ft_putstr(": ");
			}
			cp = new->inp;
			while (cp)
			{
				ft_putchar(cp->c);
				cp = cp->next;
			}
			custom_return();
		}
		new = new->previous;
		len++;
	}
	return (0);
}

int		builtin_history(char **exec, t_sh *sh)
{
	int		err;
	int		i;
	char	*fg;
	int		lg;

	fg = ft_strdup("000");
	if ((err = built_err(exec, fg)) > 0)
		return (err);
	if (fg[0] == 'A' && fg[1] == 'C')
	{
		free(fg);
		return (show_err(4, '0'));
	}
	lg = -1;
	if (!(err = get_beg(&i, &sh->history, exec)) && 
			!(err = get_lg(&lg, exec)))
	{
		i = (fg[0] == 'A') ? -1 : i;
		lg = (lg == -1 || fg[0] == 'A') ? history_len(&sh->history) : lg;
		i = (i == 0) ? -1 : i;
		i = (i > 0) ? i + 1 : i;
		err = builtin_hist(i, &sh->history, lg, fg);
	}
	free(fg);
	return (err);
}
