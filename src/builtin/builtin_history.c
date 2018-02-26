/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:11:21 by drecours          #+#    #+#             */
/*   Updated: 2018/02/26 19:02:46 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int		show_err(int err, char c, char *fg)
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
		ft_putstr_fd("history: Argument must be numerical.", STDERR_FILENO);
	custom_return();
	free(fg);
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
	if (c == '0')
	{
		i = -1;
		while (fg[++i])
			if (ft_isnum(fg[i]) == 0)
				return (1);
	}
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
				if (exec[i + 1] && exec[i + 2])
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
		else if (exec[i + 1] || put('0', exec[i]))
			return (show_err(exec[i + 1] ? 1 : 3, 'c', fg));	
	}
	return (0);
}

int		builtin_history(char **exec, t_sh *sh)
{
	t_his	*new;
	t_inp	*cp;
	int		i;
	char	*fg;

	fg = ft_strdup("000");
	if ((i = built_err(exec, fg)) > 0)
		return (i);
	i = history_len(&sh->history);
	new = sh->history;
	while (new->next)
	{
		cp = new->inp;
		while (cp)
		{
			ft_putchar(cp->c);
			cp = cp->next;
		}
		custom_return();
		new = new->next;
	}
	ft_putstr(fg);
	free(fg);
	return (0);
}
