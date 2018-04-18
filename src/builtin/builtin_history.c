/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:11:21 by drecours          #+#    #+#             */
/*   Updated: 2018/04/18 17:40:56 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int		show_err(int err, char c, char *fg)
{
	if (fg)
		free(fg);
	if (err == 1)
		ft_putendl_fd("history: Too many arguments.", STDERR_FILENO);
	if (err == 2)
	{
		ft_putstr_fd("history: illegal option -- ", STDERR_FILENO);
		ft_putchar_fd(c, STDERR_FILENO);
		ft_putstr_fd("\nusage: history [-n] [[-C|c]", STDERR_FILENO);
		ft_putendl_fd(" | [-I [args ...]] | [[-A] [[0]n]]]", STDERR_FILENO);
	}
	if (err == 3)
		ft_putendl_fd("history: Arguments must be numerical.", STDERR_FILENO);
	if (err == 4)
		ft_putendl_fd("history: I|A + C|c  together is illegal", STDERR_FILENO);
	return (err);
}

int		put(char c, char *fg)
{
	if (c == 'A')
		fg[0] = 'A';
	if (c == 'C')
		fg[1] = 'C';
	if (c == 'n')
		fg[2] = 'n';
	if (c == 'c')
		fg[3] = 'c';
	if (c == 'I')
		fg[4] = 'I';
	return (0);
}

int		built_err(char **exec, char *fg)
{
	int			i;
	int			j;
	const char	*flag = "ACncI";

	i = 0;
	j = 0;
	while (exec[++i])
	{
		if (ft_strcmp("--", exec[i]) == 0)
		{
			if (exec[i + 1] && exec[i + 2] && exec[i + 3])
				return (show_err(1, 'c', fg));
			return (0);
		}
		if (exec[i][0] == '-')
		{
			while (exec[i][++j])
				if (ft_strchr(flag, exec[i][j]) == NULL || put(exec[i][j], fg))
					return (show_err(2, exec[i][j], fg));
			j = 0;
		}
		else
			return (check_arg(exec, i));
	}
	return (0);
}

int		builtin_hist(int i, t_his **hist, int lg, char *fg)
{
	int		len;
	int		max;
	int		pos;
	t_his	*his;

	len = 0;
	his = *hist;
	pos = (i <= 0) ? 1 : 0;
	i = (i < 0) ? -i : i;
	if (lg == 0)
		return (0);
	while (his->next)
		his = his->next;
	max = history_len(hist);
	while (his->previous)
	{
		if (fg[0] == 'A' || (pos == 1 && in_it(len, i, max, lg)) ||
				(pos == 0 && in_this(len, i, max, lg)))
			show_line(fg[2], len, his->inp);
		his = his->previous;
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

	fg = ft_strdup("00000");
	lg = -1;
	if (too_big(exec) || (err = built_err(exec, fg)) > 0)
		return (erase_fg(fg, 3));
	if ((fg[0] == 'A' || fg[4] == 'I') && (fg[1] == 'C' || fg[3] == 'c'))
		return (erase_fg(fg, 4));
	if (fg[4] == 'I')
		err = insert_args(fg, sh, exec);
	else if (fg[1] == 'C' || fg[3] == 'c')
		err = history_clean(fg, &sh->history, sh);
	else if (!(err = get_beg(&i, &sh->history, exec)) &&
			!(err = get_lg(&lg, exec)))
	{
		lg = (lg == -1) ? history_len(&sh->history) : lg;
		i = (i > 0) ? i + 1 : i;
		err = builtin_hist(i, &sh->history, lg, fg);
	}
	return (erase_fg(fg, err));
}
