/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:01:36 by drecours          #+#    #+#             */
/*   Updated: 2018/04/09 11:51:55 by drecours         ###   ########.fr       */
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
int		builtin_color(char **exec, t_sh *sh);

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
int		match_name(char *env, char *name);
int		ft_isnum(char c);
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
void	free_list(t_env **env);
int		flag_v(char **exec);
int		valid_name(char *str, char *builtin);

/*
** CD TOOLS
*/
int		resolve_relative_path(t_env **env, char *bin_path);
size_t	path_trim(char *path, size_t size);
size_t	path_subcpy(const char *source, char *dest, size_t start, size_t len);
int		path_val(char *path);
int		custom_chdir(char *path, int flag, t_env **env);
char	*path_join(const char *path, const char *bin);
int		check_flag(int flag, char letter);
int		parse_flags(char **exec, int *index);
int		fix_root(char *path);
int		dir_exists(char *path);

/*
** HISTORY TOOLS
*/
void	hist_verbose(int i);
int		change_fd(t_sh *sh, char *path);
int		history_clean(char c, t_his **hist, t_sh *sh);
int		show_err(int err, char c, char *fg);
int		get_lg(int *lg, char **exec);
int		get_beg(int *i, t_his **history, char **exec);
int		last_command(t_sh *sh, t_inp **t);
int		by_last(t_sh *sh, t_inp **t, int pos);
int		history_exclaim(t_inp **inp, t_sh *sh);
int		get_by_last(t_inp *inp, t_sh *sh, t_inp **input);
int		get_by_first(t_inp *inp, t_sh *sh, t_inp **input);
int		get_by_beg(t_inp *inp, t_sh *sh, t_inp **input);
int		get_by_name(t_inp *inp, t_sh *sh, t_inp **input);
void	fill_str(t_inp *inp, char (*str)[20]);
int		no_event(int i);
int		name_no_event(int i, t_inp *inp, int pos);
int		find_in_his(t_inp *his, t_inp *inp, int *i, int flag);
int		nothing_front_back(t_inp **input, int i);
void	pt_next(t_inp **input, int i);
void	suppr_exclaim(t_inp **inp, int i, t_sh *sh);
t_inp	*insert_inp(t_inp **inp, char c);
void	suppr_letter(t_inp **c);
char	**env_in_tab(t_env **env);

#endif
