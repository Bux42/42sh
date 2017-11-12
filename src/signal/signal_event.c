/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:37:40 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 03:41:45 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		signal_event(int signo)
{
	if (signo == SIGINT)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &g_old_term);
		exit(1);
	}
}

void		signal_init(void)
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
