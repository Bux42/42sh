/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:15:45 by drecours          #+#    #+#             */
/*   Updated: 2018/04/05 06:09:11 by videsvau         ###   ########.fr       */
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
	if (!(path = command_path(&sh->env, exec[0], sh)))
		return (127);
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

int			free_and_return(char **tab, char *str, int nb)
{
	if (tab)
		env_free(tab);
	if (str)
		free(str);
	return (nb);
}

int			builtin_env(char **exec, t_sh *sh)
{
	char	**tab;
	int		i;
	int		verbose;

	i = 0;
	verbose = 0;
	if (!exec[1])
		return (print_env(&sh->env));
	if ((tab = env_in_tab(&sh->env)))
	{
		if (flag_v_u_i(&tab, exec, &verbose))
		{
			if (!(i = flag_equal(&tab, exec, verbose)))
				return (free_and_return(tab, NULL, 2));
			if (!exec[i])
				return (print_env_tab(tab));
			i = exec_cmd(tab, &(exec[i]), sh);
			env_free(tab);
			return (i);
		}
		env_free(tab);
	}
	else
		return (1);
	return (0);
}
