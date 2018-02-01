/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:15:45 by drecours          #+#    #+#             */
/*   Updated: 2018/02/01 14:13:56 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

static int			print_env_tab(char **tab)
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
	return (1);
}

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
		env->next  = new_env(tab[i]);
		i++;
		env = env->next;
	}
	return (first);
}

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

int					exec_cmd(t_env *new_env, char **tab,
		char **exec, int verbose)
{
	int		i;
	int		j;
	char	*path;
	(void)verbose;

	i = 0;
	j = 0;
	if (verbose > 0)
		show_args(exec);
	if (!(path = existing_command(exec[0], &new_env)))
	{
		ft_putstr("env: ");
		ft_putstr(exec[0]);
		ft_putstr(": No such file or directory");
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

int					builtin_env(char **exec, t_env **env)
{
	char	**tab;
	int		i;
	int		verbose;
	t_env	*new_env;

	i = 0;
	verbose = 0;
	if (exec[1])
	{
		if (!(tab = env_in_tab(env)))
			return (-1);
		if (flag_v_u_i(&tab, exec, &verbose))
		{
			tab = flag_i(tab, exec, verbose);
			if (!(i = flag_equal(&tab, exec, verbose)))
				return (0);
			if (!exec[i])
				return (print_env_tab(tab));
			else
			{
				new_env = tab_in_env(tab);
				exec_cmd(new_env, tab, &(exec[i]), verbose);
				env_free(tab);
				free_list(&new_env);
				return (i);
			}
		}
	}
	if (!exec[1])
		print_env(env);
	return (1);
}
