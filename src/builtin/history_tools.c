/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 11:58:27 by drecours          #+#    #+#             */
/*   Updated: 2018/03/05 12:26:00 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int			get_beg(int *first, t_his **history, char **exec)
{
	int		i;
	int		ite;

	i = 0;
	ite = -1;
	while (exec[++i] && exec[i][0] == '-')
		if (ft_strcmp(exec[i], "--") == 0)
		{
			i++;
			break ;
		}
	if (!exec[i])
		*first = 10;
	if (!exec[i])
		return (0);
	while (exec[i][++ite])
		if (ft_isnum(exec[i][ite]) == 0)
			return (show_err(3, '0'));
	if (exec[i])
		*first = (exec[i][0] == '0') ? ft_atoi(&exec[i][1]) : ft_atoi(exec[i]);
	if (!exec[i] || *first > history_len(history))
		*first = 0;
	*first = (exec[i][0] == '0') ? -(*first) : *first;
	return (0);
}

int			get_lg(int *lg, char **exec)
{
	int		i;
	int		ite;

	i = 1;
	ite = -1;
	while (exec[i] && exec[i][0] == '-')
	{
		if (ft_strcmp(exec[i], "--") == 0)
		{
			i++;
			break ;
		}
		i++;
	}
	if (!exec[i] || !exec[i + 1])
	{
		*lg = -1;
		return (0);
	}
	while (exec[i + 1][++ite])
		if (ft_isnum(exec[i + 1][ite]) == 0)
			return (show_err(3, '0'));
	*lg = ft_atoi(exec[i + 1]);
	*lg = (*lg < 0) ? *lg * -1 : *lg;
	return (0);
}

int			history_clean(char c, t_his **hist)
{
	ft_putstr("Cleared");
	custom_return();
	if (c == 'n')
		hist_verbose(history_len(hist));
	while ((*hist) && (*hist)->next)
	{
		(*hist) = (*hist)->next;
		free_list_from_beginning(&(*hist)->previous->inp);
		free((*hist)->previous);
	}
	if (*hist)
	{
		free_list_from_beginning(&(*hist)->inp);
		free(*hist);
		*hist = NULL;
	}
	return (0);
}

int		check_arg(char **exec, int i)
{
	if (exec[i + 1] && exec[i + 2])
		return (show_err(1, '0'));
	return (0);
}

void	show_line(char c, int nb, t_inp *cp)
{
	if (c == 'n')
	{
		ft_putnbr(nb);
		ft_putstr(": ");
	}
	while (cp)
	{
		ft_putchar(cp->c);
		cp = cp->next;
	}
	custom_return();
}
