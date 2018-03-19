/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:18:57 by drecours          #+#    #+#             */
/*   Updated: 2018/03/19 15:38:31 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"

int			print_env(t_env **env)
{
	t_env	*cp;

	if ((cp = (*env)))
	{
		while (cp)
		{
			ft_putstr(cp->env);
			custom_return();
			cp = cp->next;
		}
	}
	return (0);
}

void		new_hash(t_sh *sh, char *value)
{
	hash_del(&sh->hash, sh);
	sh->hash = hash_table(value, sh);
}

int			parse_setenv(char **exec, t_env **env, t_sh *sh)
{
	char	*name;
	char	*value;
	int		len;

	len = 0;
	value = NULL;
	name = NULL;
	while (exec[1][len] && exec[1][len] != '=')
		len++;
	if (!(name = (char*)malloc(sizeof(char) * (++len + 1))))
		return (1);
	ft_bzero(name, len);
	ft_strncat(name, exec[1], len);
	while (exec[1][len])
		len++;
	if (!(value = (char*)malloc(sizeof(char) * (len - ft_strlen(name) + 1))))
		return (1);
	ft_bzero(value, ++len - ft_strlen(name));
	ft_strcat(value, &exec[1][ft_strlen(name)]);
	set_env(env, name, value);
	if (ft_strcmp(name, "PATH=") == 0)
		new_hash(sh, value);
	free(name);
	free(value);
	return (0);
}

int			already_here(t_env **env, char **exec)
{
	t_env	*cp;
	int		stop;

	stop = 0;
	while (exec[1][stop] != '=')
		stop++;
	cp = *env;
	while (cp)
	{
		if ((ft_strncmp(exec[1], cp->env, stop)) == 0)
			return (0);
		cp = cp->next;
	}
	return (1);
}

int			builtin_setenv(char **exec, t_sh *sh)
{
	int		i;
	int		equal;
	t_env	**env;

	i = -1;
	equal = 0;
	env = &sh->env;
	if (!exec[1])
		return (print_env(env));
	if (exec[2] && exec[3])
		return (err_msg("setenv: too many arguments", "", -1));
	while (exec[1][++i])
	{
		if (exec[1][i] == '=')
			equal++;
		if (exec[1][i] == '=')
			if (i < 1)
				return (err_msg("setenv: parse error near '='", "", -1));
	}
	if (exec[2] && exec[2][0] == '0' && exec[2][1] == '\0')
		if (already_here(env, exec) == 0)
			return (0);
	if (!equal)
		return (err_msg("setenv: missing '='", "", -1));
	return (parse_setenv(exec, env, sh));
}
