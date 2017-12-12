/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 03:14:53 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/12 01:07:07 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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
	return (1);
}
