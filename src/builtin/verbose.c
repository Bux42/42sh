/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 12:40:44 by drecours          #+#    #+#             */
/*   Updated: 2018/03/03 13:20:40 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

void	nb_verb(int *verbose)
{
	char	*str;

	(*verbose)++;
	if (*verbose > 1)
	{
		ft_putstr("#env verbosity now at ");
		str = ft_itoa(*verbose);
		ft_putstr(str);
		free(str);
		custom_return();
	}
}

int		illegal_opt(char c)
{
	if (c == 'u')
		ft_putstr("env: option requires an argument -- u");
	else
	{
		ft_putstr("env: illegal option -- ");
		ft_putchar(c);
	}
	custom_return();
	return (0);
}

void	unset_verb(int verbose, char *str, char *next, char ***tab)
{
	str = (str[1]) ? &str[1] : next;
	*tab = unsetenv_tab(*tab, str);
	if (verbose > 0)
	{
		ft_putstr("#env: unset    ");
		ft_putstr(str);
		custom_return();
	}
}
