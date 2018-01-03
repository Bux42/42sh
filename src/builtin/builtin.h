/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:01:36 by drecours          #+#    #+#             */
/*   Updated: 2018/01/03 13:29:58 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../inc/typedef.h"
# include "../../inc/header.h"

/*
** BUILTINS
*/
int		unset_env_cmd(char **exec, t_env **env);
int		builtin_echo(char **exec, t_env **env);
/*int		builtin_exit(char **input);
//C EST UN GROS BORDEL ENTRE DEUX CODES POUR LE MOMENT
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
