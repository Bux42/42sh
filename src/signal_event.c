/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:48:19 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/09 22:05:09 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void			signal_event(int signo)
{
	if (signo == SIGINT)
		exit_term(signo);
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
