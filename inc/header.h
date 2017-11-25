/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 05:15:24 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/25 08:59:14 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define TERM "xterm-256color"
# include <termcap.h>
# include <termios.h>
# include <curses.h>
# include <sys/stat.h>
# include <dirent.h>
# include "../libft/includes/libft.h"

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

typedef struct			s_inpl
{
	struct s_inp		*inp;
	struct s_inpl		*next;
}						t_inpl;

typedef struct			s_his
{
	struct s_inp		*inp;
	struct s_his		*next;
	struct s_his		*previous;
}						t_his;

typedef struct			s_sh
{
	char				*tty;
	char				*home_env;
	char				*clipboard;
	char				*comp_debug;
	char				*comp_remain;
	char				*comp_path;
	int					old_len;
	char				buff[6];
	int					fd;
	int					posy;
	int					prompt_len;
	int					pos_at;
	int					inp_len;
	int					history_len;
	struct s_his		*history_pos;
	int					width;
	int					retval;
	char				pwd[2048];
	struct s_env		*env;
	struct s_inpl		*inpl;
	struct s_his		*history;
}						t_sh;

/*						initialize_term									*/

struct termios			g_old_term;
struct termios			g_new_term;

int						init_term(void);
void					signal_init(void);
void					signal_event(int signo);

/*						environment										*/

char					*get_specific_env(char *env, t_env **envlist);
void					get_env(char **env, t_sh *sh);
void					env_push_back(t_env **envlist, char *env);
t_env					*new_env(char *env);

/*						pwd_stuff										*/

void					print_prompt(t_sh *sh);
void					tild_prompt(t_sh *sh);
void					prompt_colors(int i);

/*						line_edition									*/

void					free_null(char **str);

void					treat_input(t_sh *sh);
void					add_delete_letter(t_sh *sh);
void					delete_letter(t_sh *sh, t_inp **inp);
void					delete_beginning(t_inp **inp, t_inp *cp);
void					delete_after(t_sh *sh, t_inp **inp);
void					overwrite_remaining(t_sh *sh, t_inp **inp);
void					overwrite_deleted(t_sh *sh, t_inp **inp);
int						check_dimentions(t_sh *sh);
void					check_endline(t_sh *sh);

void					move_cursor(t_sh *sh, t_inp **inp, char c);
void					move_left(t_sh *sh, t_inp **inp);
void					move_right(t_sh *sh, t_inp **inp);
int						custom_left(t_sh *sh);
int						custom_right(t_sh *sh);

int						is_space(char c);
void					jump_words(t_sh *sh, char c);
void					jump_left(t_sh *sh, t_inp **inp);
void					jump_right(t_sh *sh, t_inp **inp);
void					home_end(t_sh *sh, t_inp **inp, int active);

void					jump_up(t_sh *sh, t_inp **inp);
void					jump_down(t_sh *sh, t_inp **inp);

t_inp					*new_inp(char c);
void					inp_insert_posat(t_inp **inp, char c);
void					insert_middle(t_inp *first, t_inp *tmp);
void					insert_first(t_inp *first, t_inp *tmp, t_inp **inp);
void					insert_beginning(t_inp *first, t_inp *tmp);

t_inp					*get_to_pos(t_inp **inp);
int						pos_at(t_inp **inp, int len);
int						inp_list_len(t_inp **inp);

void					check_shortcut(t_sh *sh);
void					cut_after(t_sh *sh, t_inp **inp);
void					cut_before(t_sh *sh, t_inp **inp);
char					*get_clipboard(t_inp *inp, int *dec, t_sh *sh);
char					*get_clipboard_before(t_inp *inp, int *dec, t_sh *sh);
void					free_list_from_here(t_inp *cp);
void					free_list_from_beginning(t_inp **inp);
void					free_list_before(t_inp *cp);

void					paste_after(t_sh *sh, t_inp **inp);

void					history_push_front(t_his **history, t_inp *inp);
t_his					*history_new(t_inp *inp);
int						history_len(t_his **history);

void					search_history_backward(t_sh *sh, t_his **history);
void					search_history_forward(t_sh *sh, t_his **history);
void					search_history_inp(t_sh *sh, t_inp **inp);
void					clear_line(t_sh *sh, t_inp **inp);

char					*inp_to_char(t_inp **inp, t_sh *sh);
void					restaure_history_from_file(t_sh *sh);
int						check_empty_line(t_inp **inp);

/*						auto_completion									*/

void					autocompletion(t_inp **inp, t_sh *sh);
void					print_completiong(t_sh *sh, t_inp **inp);
void					insert_completion(t_sh *sh, t_inp **inp);
void					erase_completion(t_sh *sh, t_inp **inp);
char					*get_left_word(t_inp *cp, t_sh *sh);
void					overwrite_remaining_comp(t_sh *sh, t_inp **inp, int i);
void					free_comp(int i, t_sh *sh);
void					print_spaces(int nb, t_sh *sh);
void					rewrite_beginning(t_sh *sh, t_inp *cp);

/*						tty_debug										*/

int						get_tty(t_sh *sh, char *av);
void					tty_debug(t_sh *sh, t_inp **inp);

#endif
