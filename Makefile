# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/17 14:50:04 by vboivin           #+#    #+#              #
#    Updated: 2018/04/11 10:23:52 by drecours         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= 21sh
HPATH		= includes
INC			= -I$(HPATH) -Ilibft/includes
FLAGS		= -Wall -Werror -Wextra #-fsanitize=address -g3 #-fbounds-check
COMP		= gcc
LIBFT		= -Llibft -lft -lcurses

SRCS	=	\
main/main.c\
tty_debug/tty_debug.c\
tty_debug/optimized_tools.c\
line_edition/treat_input.c\
line_edition/clear_screen.c\
line_edition/heredoc_treat_input.c\
line_edition/add_delete_letter.c\
line_edition/check_shortcut.c\
line_edition/paste_after.c\
line_edition/delete_after.c\
line_edition/move_cursor.c\
line_edition/jump_words.c\
line_edition/jump_up_down.c\
line_edition/home_end.c\
line_edition/inp_list.c\
line_edition/history_list.c\
line_edition/history_tools.c\
line_edition/list_to_char.c\
line_edition/search_history_forward.c\
line_edition/auto_completion.c\
line_edition/auto_completion_tools.c\
line_edition/auto_completion_clear.c\
line_edition/completion_path.c\
line_edition/print_completion.c\
line_edition/auto_completion_builtin.c\
line_edition/line_is_closed.c\
line_edition/s_close_list.c\
line_edition/enter_key.c\
line_edition/history_search.c\
line_edition/treat_input_search.c\
line_edition/insert_search_history_result.c\
line_edition/print_search.c\
line_edition/optimized_tools.c\
line_edition/optimized_tools_2.c\
line_edition/inpl_list.c\
line_edition/s_bin_list.c\
parsing/debug.c\
parsing/heredoc.c\
parsing/heredoc_tools.c\
parsing/token_list.c\
parsing/tokenize_splitted.c\
parsing/tokenize_splitted_tools.c\
parsing/check_tokenize.c\
parsing/t_redir_list.c\
parsing/convert_quotes.c\
parsing/convert_quotes_tools.c\
parsing/check_special.c\
parsing/check_special_redir.c\
parsing/check_special_surrounding.c\
parsing/convert_splitted.c\
parsing/split_line.c\
parsing/split_line_tools.c\
parsing/parse_line.c\
parsing/redirections.c\
parsing/variable.c\
parsing/insert_home.c\
parsing/context_updater.c\
exec/pipe.c\
exec/redir.c\
exec/redir_tools.c\
exec/main_exec.c\
exec/execute_tokens.c\
exec/execute_tokens_old.c\
exec/fork_command.c\
exec/print_error.c\
exec/aggregations.c\
builtin/check_builtin.c\
builtin/change_dir.c\
signal/signal_event.c\
launch_term/init_term.c\
env/env_list.c\
env/get_env.c\
pwd/print_prompt.c\
builtin/builtin_history.c\
builtin/builtin_echo.c\
builtin/builtin_exit.c\
builtin/builtin_unsetenv.c\
builtin/builtin_setenv.c\
builtin/builtin_env.c\
builtin/env_flag_vui.c\
builtin/env_flag_equal_i.c\
builtin/env_tools.c\
builtin/tab_builtin.c\
builtin/builtin_set.c\
builtin/builtin_local.c\
builtin/builtin_unset.c\
builtin/builtin_export.c\
builtin/dir_tools.c\
builtin/dir_tools2.c\
builtin/builtin_myman.c\
builtin/history_tools.c\
builtin/verbose.c\
builtin/env_tools2.c\
builtin/history_exclaim.c\
builtin/exclaim_tools.c\
builtin/history_find.c\
builtin/exclaim_tools2.c\
builtin/exclaim_misc.c\
builtin/dir_tools3.c\
builtin/color.c\
builtin/set_tools.c\
hash/hash.c\
hash/hash_functions.c\
hash/init_hash.c

RED='\e[1;31m'
GRN='\e[1;32m'
YEL='\e[1;33m'
BLU='\e[1;34m'
MAG='\e[1;35m'
CYN='\e[1;36m'
END='\e[0m'

DIR_SRC		= $(addprefix $(SRCPATH)/, $(SRCS))
SRCPATH		= src

OBJ 		= $(SRCS:.c=.o)
OBJPATH		= objs
DIR_OBJ		= $(addprefix $(OBJPATH)/, $(OBJ))

all: $(NAME)

$(OBJPATH)/%.o: $(SRCPATH)/%.c
	@printf "\33[KCompiling `printf $(RED)`$<`printf $(END)`\r"
	@$(COMP) $(FLAGS) -MMD -c $< -o $@ $(INC)

make_objs:
	@mkdir -p $(OBJPATH)
	@mkdir -p $(dir $(DIR_OBJ))

$(NAME): make_objs $(DIR_OBJ)
	@printf "\33[Kmain obj compil:\t`printf $(GRN)`done\t✅`printf $(END)`\n"
	@make -C libft
	@printf "\33[Klibft compil:\t\t`printf $(GRN)`done\t✅`printf $(END)`\n"
	@echo "vboivin:jamerlin" > auteur
	@$(COMP) $(DIR_OBJ) -o $(NAME) $(INCMAC) $(LIBFT) $(FLAGS) 
	@printf "main compilation:\t`printf $(GRN)`done\t✅`printf $(END)`\n"

clean:
	@make clean -C libft
	@rm -rf $(DIR_OBJ)

fclean: rmtest
	@printf "\33[K`printf $(RED)`Crushing \t\t\t☠️`printf $(END)`\r"
	@make fclean -C libft
	@rm -rf $(DIR_OBJ)
	@rm -rf $(NAME)
	@printf "\33[K`printf $(GRN)`Crushing done\t\t\t🗑️`printf $(END)`\n"

test:
	@mkdir test_dir
	@mkdir test_dir/test_rec
	@mkdir test_dir/test_rec2
	@touch test_dir/test_file
	@touch test_dir/test_file2
	@chmod 7000 test_dir/test_file
	@chmod 7777 test_dir/test_file2
	@ln -s test_dir/test_file test_dir/test_link

rmtest:
	@rm -rf test_dir

re: fclean all

.PHONY :			fclean clean re all make_objs test rmtest
