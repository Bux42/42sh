/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_flag_equal_i.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:51:01 by drecours          #+#    #+#             */
/*   Updated: 2018/01/15 19:00:03 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"
#include "builtin.h"


char	**env_add(char **env, const char *env_val)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while (env[i] != NULL)
		++i;
	if (!(new_env = malloc((i + 2) * sizeof(char*))))
	{
		write(STDERR_FILENO, "Malloc error.\n", 14);
		return (env);
	}
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = env[i];
		++i;
	}
	new_env[i] = ft_strdup(env_val);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

char	**env_write(char **env, const char *key, const char *val)
{
	size_t	i;
	char	*new_env;
	char	*tmp_env;

	tmp_env = ft_strjoin(key, "=");
	new_env = ft_strjoin(tmp_env, val);
	free(tmp_env);
	i = 0;
	while (env[i] != NULL)
	{
		tmp_env = env_key(env[i]);
		if (ft_strcmp(tmp_env, key) == 0)
		{
			free(tmp_env);
			free(env[i]);
			env[i] = new_env;
			return (env);
		}
		free(tmp_env);
		++i;
	}
	env = env_add(env, new_env);
	free(new_env);
	return (env);
}

char	**env_error(char **new_env, char *str)
{
	char	*key;
	char	*tmp;

	if (str[0] == '=')
	{
		env_free(new_env);
		new_env = NULL;
		write(STDERR_FILENO, "env: setenv ", 12);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, ": Invalid argument\n", 19);
		return (NULL);
	}
	else
	{
		key = ft_strchr(str, '=') + 1;
		tmp = env_key(str);
		new_env = env_write(new_env, tmp, key);
		free(tmp);
	}
	return (new_env);
}

int		flag_equal(char ***tab, char **exec, int verbose)
{
	int		i;
	int		x;
	(void)tab;

	i = 0;
	x = 0;
	while (exec[++i] && (exec[i][0] == '-' || (ft_strchr(&exec[i][1], '=') && 
					exec[i][0] != '=')))
	{
		if (exec[i][0] == '-')
		{
			x = 0;
			while (exec[i][++x])
				if (exec[i][x] == 'u')
				{
					if (!exec[i][x + 1])
						i++;
					break ;
				}
		}
		else
		{
			if (verbose > 0)
			{
				ft_putstr("#env: setenv    ");
				ft_putstr(exec[i]);
				custom_return();
			}
			if (!(*tab = env_error(*tab, exec[i])))
				return (-1);
		}
	}
	return (i);
}

char	**flag_i(char **tab, char **exec, int verbose)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (exec[++i] && (exec[i][0] == '-' || (ft_strchr(&exec[i][1], '=') &&
					exec[i][0] != '=')))
		if (exec[i][0] == '-')
		{
			x = 1;
			while (exec[i][x])
			{
				if (exec[i][x] == 'u')
				{
					if (!exec[i][x + 1])
						i++;
					break ;
				}
				if (exec[i][x] == 'i' || exec[i][x] == '-')
				{
					if (verbose > 0)
					{
						ft_putstr("#env clearing environ");
						custom_return();
					}
					env_free(tab);
					if (!(tab = (char**)malloc(sizeof(char*) * 1)))
						return (NULL);
					tab[0] = NULL;
					return (tab);
				}
				x++;
			}
		}
	return (tab);
}
