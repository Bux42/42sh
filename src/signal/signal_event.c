/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:37:40 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/22 14:01:35 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		signal_newline(int inp)
{
	(void)inp;
	custom_return();
}

void		free_closing(t_sh *sh, t_close **close)
{
	t_close	*cp;
	t_close *tmp;

	if ((cp = (*close)))
	{
		while (g_sh->inpl && g_sh->inpl->previous)
		{
			free_list_from_beginning(&g_sh->inpl->inp);
			g_sh->inpl = g_sh->inpl->previous;
			free(g_sh->inpl->next);
			g_sh->inpl->next = NULL;
		}
		free_list_from_beginning(&g_sh->inpl->inp);
		while (cp)
		{
			tmp = cp;
			cp = cp->next;
			free(tmp);
		}
		sh->close = NULL;
	}
}

void		signal_print_prompt(int inp)
{
	(void)inp;
	custom_return();
	g_sh->retval = 1;
	print_prompt(g_sh);
	free_comp(11, g_sh);
	g_sh->context = 0;
	if (g_sh->search)
	{
		free_list_from_beginning(&g_sh->inpl->inp);
		g_sh->search = 0;
		ft_putstr(tgetstr("ve", NULL));
	}
	else if (!g_sh->close)
		free_list_from_beginning(&g_sh->inpl->inp);
	else
		free_closing(g_sh, &g_sh->close);
}

void		signal_init(void)
{
	signal(SIGINT, &signal_print_prompt);
	signal(SIGHUP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGILL, SIG_IGN);
	signal(SIGTRAP, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGKILL, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
}

void		signal_exec(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGHUP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGILL, SIG_DFL);
	signal(SIGTRAP, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGKILL, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGSTOP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
}
