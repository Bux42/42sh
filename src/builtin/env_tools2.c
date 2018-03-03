/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 14:42:12 by drecours          #+#    #+#             */
/*   Updated: 2018/03/03 14:43:58 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

t_env				*tab_in_env(char **tab)
{
	t_env	*env;
	t_env	*first;
	int		i;

	i = 0;
	first = NULL;
	if (tab[0])
		first = new_env(tab[0]);
	env = first;
	while (tab[i])
	{
		env->next = new_env(tab[i]);
		i++;
		env = env->next;
	}
	return (first);
}

void				show_args(char **exec)
{
	int		i;
	char	*j;

	i = 0;
	ft_putstr("#env executing: ");
	ft_putstr(exec[i]);
	custom_return();
	while (exec[i])
	{
		ft_putstr("#env    arg[");
		j = ft_itoa(i);
		ft_putstr(j);
		free(j);
		ft_putstr("]= '");
		ft_putstr(exec[i]);
		ft_putstr("'");
		custom_return();
		i++;
	}
}
