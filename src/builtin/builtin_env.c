/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:15:45 by drecours          #+#    #+#             */
/*   Updated: 2018/03/19 15:35:16 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int			print_env_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		custom_return();
		i++;
	}
	env_free(tab);
	return (0);
}

char		**env_in_tab(t_env **env)
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

int			exec_cmd(t_env *new_env, char **tab, char **exec, t_sh *sh)
{
	int		i;
	char	*path;

	i = 0;
	if (flag_v(exec))
		show_args(exec);
	if (!(path = existing_command(exec[0], &new_env, sh)))
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(exec[0], 2);
		ft_putstr_fd(": No such file or directory", 2);
		custom_return();
		i = 127;
		return (i);
	}
	else
	{
		i = fork_command(path, exec, tab);
		free(path);
	}
	return (i);
}

void		free_list(t_env **env)
{
	t_env	*cp;
	t_env	*tmp;

	tmp = NULL;
	if ((cp = (*env)))
	{
		while (cp)
		{
			if (cp->env)
				free(cp->env);
			tmp = cp;
			cp = cp->next;
			free(tmp);
		}
		(*env) = NULL;
	}
}

int			builtin_env(char **exec, t_sh *sh)
{
	char	**tab;
	int		i;
	int		verbose;
	t_env	*new_env;

	i = 0;
	verbose = 0;
	if (!exec[1])
		return (print_env(&sh->env));
	if (!(tab = env_in_tab(&sh->env)))
		return (1);
	if (flag_v_u_i(&tab, exec, &verbose))
	{
		tab = flag_i(tab, exec, verbose);
		if (!(i = flag_equal(&tab, exec, verbose)))
			return (2);
		if (!exec[i])
			return (print_env_tab(tab));
		new_env = tab_in_env(tab);
		i = exec_cmd(new_env, tab, &(exec[i]), sh);
		env_free(tab);
		free_list(&new_env);
		return (i);
	}
	return (0);
}
