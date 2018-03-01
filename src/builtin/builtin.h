/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:01:36 by drecours          #+#    #+#             */
/*   Updated: 2018/03/01 14:21:33 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../inc/typedef.h"
# include "../../inc/header.h"

/*
** BUILTINS
*/
int		builtin_setenv(char **exec, t_sh *sh);
int		builtin_unsetenv(char **exec, t_sh *sh);
int		builtin_echo(char **exec, t_sh *sh);
int		builtin_exit(char **exec, t_sh *sh);
int		builtin_env(char **exec, t_sh *sh);
int		builtin_set(char **exec, t_sh *sh);
int		builtin_local(char **exec, t_sh *sh);
int		builtin_unset(char **exec, t_sh *sh);
int		builtin_export(char **exec, t_sh *sh);
int		builtin_myman(char **exec, t_sh *sh);
int		builtin_cd(char **exec, t_sh *sh);
int		builtin_history(char **exec, t_sh *sh);

int		print_env(t_env **env);
void	set_env(t_env **env, char *name, char *value);
int		flag_v_u_i(char ***tab, char **exec, int *verbose);
char	**flag_i(char **tab, char **exec, int verbose);
int		flag_equal(char ***tab, char **exec, int verbose);
char	**unsetenv_tab(char **env, char *key);
int 	env_free(char **env);
char	*env_key(char *env_v);
int		matching_name(char *env, char *name);
int		ft_isnum(char c);
size_t	path_subcpy(const char *source, char *dest, size_t start, size_t len);
size_t	path_trim(char *path, size_t size);
int		get_beg(int *i, t_his **history, char **exec);
int		get_lg(int *lg, char **exec);
int		history_clean(char c, t_his **hist);
int		show_err(int err, char c);

#endif
