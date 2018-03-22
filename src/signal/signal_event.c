/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:37:40 by videsvau          #+#    #+#             */
/*   Updated: 2018/01/16 18:45:46 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		signal_newline(int inp)
{
	(void)inp;
	write(1, "\n", 1);
}

void		signal_print_prompt(int inp)
{
	(void)inp;
	custom_return();
	print_prompt(g_sh);
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
