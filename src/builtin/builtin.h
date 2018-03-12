/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:01:36 by drecours          #+#    #+#             */
/*   Updated: 2018/03/12 17:50:44 by drecours         ###   ########.fr       */
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
int		resolve_relative_path(t_env **env, char *bin_path);
int		path_val(char *path);
int		custom_chdir(char *path, int flag, t_env **env);
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
int		by_last(t_inp **inp, t_sh *sh, t_inp **t, int pos);
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
void	suppr_exclaim(t_inp **inp, int i);
t_inp	*insert_inp(t_inp **inp, char c);
void	suppr_letter(t_inp **c);


/*
** TEST
*/
int	ft_cd(char **stock, t_sh *sh);
int	return_dot(char *path, char *option);
int	error_environ(t_env **env, char *path, char *option);
//void	ft_set_path(&tmp, &path, &option, t_env **env);
int		return_usage(char *path, char *option);
int		return_cd_bis(char *path, char *option, t_env **env, char buff[]);
void	check_cd(char *path, t_env **env, char *buff);
void	error_case1(char *path);
void	error_case2(char *path);
void	cd(t_env **env, char **path, char *buff);
void	set_old_dir(char *tmp2, char **path, t_env **env);
void	cd_l_bis(t_env **env, char **path, char *buff);
int		ft_cd_bis(char *path, char *option, t_env **env, char *buff);
int		cd_back(t_env **env);
int		cd_less(t_env **env, char *buff);
int		cd_l(t_env **env, char *option);
int		cd_p(t_env **env, char *option, char *buff);


#endif
