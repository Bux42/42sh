/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:01:36 by drecours          #+#    #+#             */
/*   Updated: 2018/03/07 17:53:05 by drecours         ###   ########.fr       */
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

/*
** BUILTIN TOOLS
*/
int		print_env(t_env **env);
void	set_env(t_env **env, char *name, char *value);
int		flag_v_u_i(char ***tab, char **exec, int *verbose);
char	**flag_i(char **tab, char **exec, int verbose);
int		flag_equal(char ***tab, char **exec, int verbose);
char	**unsetenv_tab(char **env, char *key);
int		env_free(char **env);
char	*env_key(char *env_v);
int		matching_name(char *env, char *name);
int		ft_isnum(char c);
size_t	path_subcpy(const char *source, char *dest, size_t start, size_t len);
size_t	path_trim(char *path, size_t size);
int		env_verbose(int verb, char *exec);
char	**clear_realloc(int verb, char **tab);
char	*env_key(char *env_v);
void	nb_verb(int *verbose);
int		illegal_opt(char c);
void	unset_verb(int verbose, char *str, char *next, char ***tab);
int		check_arg(char **exec, int i);
void	show_line(char c, int nb, t_inp *cp);
t_env	*tab_in_env(char **tab);
void	show_args(char **exec);
int		erase_fg(char *fg, int i);
/**/
int		resolve_relative_path(char *bin_path);
int		path_val(char *path);
int		custom_chdir(char *path);
char	*path_join(const char *path, const char *bin);
/**/

/*
** HISTORY TOOLS
*/
void	hist_verbose(int i);
int		change_fd(t_sh *sh, char *path);
int		history_clean(char c, t_his **hist, t_sh *sh);
int		show_err(int err, char c);
int		get_lg(int *lg, char **exec);
int		get_beg(int *i, t_his **history, char **exec);
int		last_command(t_inp **inp, t_sh *sh, t_inp **t);
int		by_last(t_inp **inp, t_sh *sh);
int		by_first(t_inp **inp, t_sh *sh);
int		search_that(t_inp **inp, t_sh *sh);
int		search(t_inp **inp, t_sh *sh);
int		history_exclaim(t_inp **inp, t_sh *sh);

#endif
