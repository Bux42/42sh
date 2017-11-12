/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 05:15:24 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 07:08:02 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define TERM "xterm-256color"
# include <termcap.h>
# include <termios.h>
# include <curses.h>
# include <sys/stat.h>
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

typedef struct			s_sh
{
	char				*tty;
	char				*home_env;
	char				buff[6];
	int					posy;
	int					prompt_len;
	int					pos_at;
	int					width;
	int					retval;
	char				pwd[2048];
	struct s_env		*env;
	struct s_inpl		*inpl;
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

void					treat_input(t_sh *sh);
void					add_delete_letter(t_sh *sh);
int						check_dimentions(t_sh *sh);
void					check_endline(t_sh *sh);

t_inp					*new_inp(char c);
void					inp_push_back(t_inp **inp, char c);
void					insert_middle(t_inp *first, t_inp *tmp);
void					insert_first(t_inp *first, t_inp *tmp, t_inp **inp);
void					insert_beginning(t_inp *first, t_inp *tmp);

/*						tty_debug										*/

int						get_tty(t_sh *sh, char *av);
void					tty_debug(t_sh *sh, t_inp **inp);

#endif
