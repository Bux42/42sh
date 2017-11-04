/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:46:48 by videsvau          #+#    #+#             */
/*   Updated: 2017/10/31 10:02:58 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		exit_term(int ret)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_old_term);
	exit(ret);
}

int			init_term(void)
{
	if (tcgetattr(STDIN_FILENO, &g_old_term) == -1)
		return (0);
	if (tcgetattr(STDIN_FILENO, &g_new_term) == -1)
		return (0);
	g_new_term.c_lflag &= ~(ECHO | ICANON);
	g_new_term.c_oflag &= ~(OPOST);
	g_new_term.c_cc[VMIN] = 1;
	g_new_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &g_new_term) == -1)
		return (0);
	if (!(tgetent(NULL, TERM)))
		return (0);
	signal_init();
	return (1);
}
