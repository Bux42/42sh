/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 02:12:01 by videsvau          #+#    #+#             */
/*   Updated: 2017/12/15 05:09:03 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		prompt_colors(int i)
{
	if (i == 1)
		ft_putstr("\x1b[36m");
	if (i == 2)
		ft_putstr("\x1b[32m");
	if (i == 3)
		ft_putstr("\x1b[31m");
	if (i == 0)
		ft_putstr("\x1b[0m");
}

void		tild_prompt(t_sh *sh)
{
	if (ft_strncmp(sh->home_env, sh->pwd, ft_strlen(sh->home_env)) == 0)
	{
		sh->posy += ft_strlen(&sh->pwd[ft_strlen(sh->home_env)]) + 1;
		ft_putchar('~');
		ft_putstr(&sh->pwd[ft_strlen(sh->home_env)]);
	}
	else
	{
		sh->posy += ft_strlen(sh->pwd);
		ft_putstr(sh->pwd);
	}
	free(sh->home_env);
}

void		print_prompt(t_sh *sh)
{
	sh->posy = 4;
	getcwd(sh->pwd, 2048);
	prompt_colors(1);
	if ((sh->home_env = get_specific_env("HOME=", &sh->env)))
		tild_prompt(sh);
	else
	{
		sh->posy += ft_strlen(sh->pwd);
		ft_putstr(sh->pwd);
	}
	if (sh->retval == 0)
		prompt_colors(2);
	else
		prompt_colors(3);
	ft_putstr(" » ");
	prompt_colors(0);
	sh->prompt_len = sh->posy;
}
