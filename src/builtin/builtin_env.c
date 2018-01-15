/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:15:45 by drecours          #+#    #+#             */
/*   Updated: 2018/01/15 16:22:33 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

static char			**env_in_tab(t_env **env)
{
	int		i;
	t_env	*cp;
	char	**tab;

	cp = *env;
	i = 0;
	while (cp)
	{
		i++;
		cp = cp->next;
	}
	if (!(tab = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	tab[i] = NULL;
	cp = *env;
	i = 0;
	while (cp)
	{
		if (cp->env)
			tab[i] = ft_strdup(cp->env);
		i++;
		cp = cp->next;
	}
	return (tab);
}	

int					builtin_env(char **exec, t_env **env)
{
	char	**tab;
	int		i;
	int		verbose;

	i = 0;
	verbose = 0;
	if (exec[1])
	{
		if (!(tab = env_in_tab(env)))
			return (-1);
		if (flag_v_u_i(&tab, exec, &verbose))
		{
			tab = flag_i(tab, exec, verbose);
			i = 0;
			while (tab[i])
			{
				ft_putstr(tab[i]);
				custom_return();
				i++;
			}
		}
	}
	if (!exec[1])
		print_env(env);
	return (1);
}
