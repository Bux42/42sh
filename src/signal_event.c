/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:48:19 by videsvau          #+#    #+#             */
/*   Updated: 2017/10/31 10:03:30 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void			signal_event(int signo)
{
	ft_putnbr(signo);
	if (signo == SIGINT)
		exit_term(signo);
	ft_putnbr(signo);
}

void			signal_init(void)
{
	signal(SIGINT, signal_event);
	signal(SIGHUP, signal_event);
	signal(SIGQUIT, signal_event);
	signal(SIGILL, signal_event);
	signal(SIGTRAP, signal_event);
	signal(SIGABRT, signal_event);
	signal(SIGKILL, signal_event);
	signal(SIGTERM, signal_event);
	signal(SIGTSTP, signal_event);
	signal(SIGSTOP, signal_event);
	signal(SIGCONT, signal_event);
}
