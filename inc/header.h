/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:22:07 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/08 23:50:02 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H

# define HEADER_H
# include "../libft/includes/libft.h"
# include <termcap.h>
# include <termios.h>
# include <curses.h>
# define DEBUG 1
# define TERM "xterm-256color"

typedef struct			s_env
{
	char				*env;
	struct s_env		*next;
}						t_env;

typedef struct			s_inp
{
	char				c;
	int					pos;
	struct s_inp		*next;
	struct s_inp		*previous;
}						t_inp;

typedef struct			s_cmd
{
	char				*arg;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_sh
{
	char				buff[6];
	int					debug;
	int					posy;
	int					width;
	int					retval;
	char				pwd[2048];
	struct s_env		*env;
	struct s_inp		*inp;
	struct s_inp		*clipboard;
	struct s_cmd		*cmd;
}						t_sh;

struct termios			g_old_term;
struct termios			g_new_term;

/*						char** env							*/

int						get_env(char **env, t_sh *sh);
int						matching_env(char *env, char *match);
int						valid_env(char *env);

/*						env_list							*/

t_env					*new_env(char *env);
void					env_push_back(t_env **env2, char *env);
char					*get_specific_env(char *env, t_env **envlist);

/*						debug_option						*/

void					check_debug(char **av, t_sh *sh);

/*						term_mode							*/

void					signal_event(int signo);
void					signal_init(void);
int						init_term(void);
void					exit_term(int ret);
void					continue_term(void);

/*						read_stdin							*/

void					treat_input(t_sh *sh);
t_inp					*new_inp(char c);
void					inp_push_back(t_inp **inp, char c);
void					print_inp(t_inp **inp);

/*						edit_prompt							*/

void					move_right(t_inp **inp);
void					move_left(t_inp **inp);
void					delete_pos(t_inp **inp);
void					remove_first(t_inp *cp, t_inp **inp);
void					remove_middle(t_inp *cp);
void					delete_pos_a(t_inp **inp);
void					delete_last(t_inp **inp, t_inp *cp);
void					delete_at_begining(t_inp **inp, t_inp *cp);
void					delete_middle(t_inp *cp);
void					home_end(t_inp **inp, int i);
void					jump_left_word(t_inp **inp);
void					jump_right_word(t_inp **inp);

void					restaure_input_line(t_inp **inp);
void					restaure_input_line_a(t_inp **inp);

int						condition_le(void);
int						condition_nd(void);

int						is_space(char c);

/*						auto_completion						*/

int						auto_completion(t_inp **inp);

/*						pwd stuff							*/

void					current_dir(t_sh *sh);

/*						debug stuff							*/

void					debug_file(t_inp **inp);

#endif
