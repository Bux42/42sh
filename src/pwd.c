/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 21:11:48 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/08 23:55:15 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		current_dir(t_sh *sh)
{
	char	*home;

	ft_putstr("\x1b[36m");
	sh->posy = 3;
	getcwd(sh->pwd, 2048);
	if ((home = get_specific_env("HOME=", &sh->env)))
	{
		if (ft_strncmp(&home[5], sh->pwd, ft_strlen(&home[5])) == 0)
		{
			sh->posy += ft_strlen(&sh->pwd[ft_strlen(&home[5])]) + 1;
			ft_putchar('~');
			ft_putstr(&sh->pwd[ft_strlen(&home[5])]);
		}
		else
		{
			sh->posy += ft_strlen(sh->pwd);
			ft_putstr(sh->pwd);
		}
		free(home);
	}
	else
	{
		sh->posy += ft_strlen(sh->pwd);
		ft_putstr(sh->pwd);
	}
	if (sh->retval)
		ft_putstr("\x1b[32m");
	else
		ft_putstr("\x1b[31m");
	ft_putstr(" » ");
	ft_putstr("\x1b[0m");
}
