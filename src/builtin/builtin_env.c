/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:15:45 by drecours          #+#    #+#             */
/*   Updated: 2018/04/09 14:29:14 by drecours         ###   ########.fr       */
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
		ft_putendl_fd(tab[i], STDOUT_FILENO);
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

int			exec_cmd(char **tab, char **exec, t_sh *sh)
{
	int		i;
	char	*path;

	i = 0;
	if (flag_v(exec))
		show_args(exec);
	if (!(path = existing_command(exec, &sh->env, sh, 1)))
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(exec[0], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		i = 127;
		free(path);
		return (i);
	}
	else if (ft_strcmp(path, "ok") && bin_exists(path, exec[0], &sh->retval) == 0)
	{
		i = fork_command(path, exec, tab);
	}
	if (path)
		free(path);
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
	if ((!exec[1] && print_env(&sh->env)) || !(tab = env_in_tab(&sh->env)))
		return (1);
	if (flag_v_u_i(&tab, exec, &verbose))
	{
		tab = flag_i(tab, exec, verbose);
		if (!(i = flag_equal(&tab, exec, verbose)))
			return (2);
		if (!exec[i])
			return (print_env_tab(tab));
		new_env = sh->env;
		sh->env = tab_in_env(tab);
		i = exec_cmd(tab, &(exec[i]), sh);
		env_free(tab);
		free_list(&sh->env);
		sh->env = new_env;
		return (i);
	}
	return (env_free(tab));
}
