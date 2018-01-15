/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:01:36 by drecours          #+#    #+#             */
/*   Updated: 2018/01/15 18:16:00 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../inc/typedef.h"
# include "../../inc/header.h"

/*
** BUILTINS
*/
int		builtin_setenv(char **exec, t_env **env);
int		builtin_unsetenv(char **exec, t_env **env);
int		builtin_echo(char **exec, t_env **env);
int		builtin_exit(char **exec, t_env **env);
int		builtin_env(char **exec, t_env **env);

int		print_env(t_env **env);
void	set_env(t_env **env, char *name, char *value);
int		flag_v_u_i(char ***tab, char **exec, int *verbose);
char	**flag_i(char **tab, char **exec, int verbose);
int		flag_equal(char ***tab, char **exec, int verbose);
char	**unsetenv_tab(char **env, char *key);
int 	env_free(char **env);
char	*env_key(char *env_v);


/*
int		builtin_cd(chr **input, t_list **env);
int		builtin_unsetenv(char **input, t_list **env);
int		builtin_setenv(char **input, t_list **env);
//int		builtin_env();
int		builtin_export(char **input, t_list **env, t_local **local);
int		builtin_unset(char **input, t_local **local);
int		builtin_set(char **input, t_local **env);
int		builtin_show(t_list **local);
*/
/*
** BUILTIN_LIB
*/
/*
int		lg_tab(char **input);
int		maching_name(char *env, char *name);
char	*new_env(char **input);
int		remove_first(t_list **env, t_list **cp);
int		remove_between(t_list **cp, t_list **tmp);
t_list	*chain_env(char **input);
char	**ft_strsplit(char const *str, char c);
int		cd_error(char **env, int err, char *str, t_command *command);
int		ft_path(char *pwd, char **input, t_list **env);
int		cd_error(int err, char *str, t_command *command);
int		dir_exists(char *path);
*/
#endif
