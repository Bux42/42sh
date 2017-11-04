/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 21:11:48 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/04 21:57:35 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		current_dir(t_sh *sh)
{
	char	*home;

	getcwd(sh->pwd, 2048);
	if ((home = get_specific_env("HOME=", &sh->env)))
	{
		if (ft_strncmp(&home[5], sh->pwd, ft_strlen(&home[5])) == 0)
		{
			ft_putchar('~');
			ft_putstr(&sh->pwd[ft_strlen(&home[5])]);
		}
		else
			ft_putstr(sh->pwd);
		free(home);
	}
	else
		ft_putstr(sh->pwd);
	ft_putstr(" » ");
}
