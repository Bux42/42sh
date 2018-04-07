# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/12 02:03:18 by videsvau          #+#    #+#              #
#    Updated: 2018/04/07 02:05:13 by videsvau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	21sh

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
D_FLAGS		=	-g

#-fsanitize=address

LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	$(LIBFT_DIR)includes/

LIBS		=	-ltermcap

SRC_DIR		=	src/
INC_DIR		=	includes/
OBJ_DIR		=	objs/

SRC_BASE	=	\
main/main.c\
tty_debug/tty_debug.c\
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
parsing/token_list.c\
parsing/tokenize_splitted.c\
parsing/convert_quotes.c\
parsing/check_special.c\
parsing/check_special_surrounding.c\
parsing/convert_splitted.c\
parsing/split_line.c\
parsing/parse_line.c\
parsing/lexer_parser.c\
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
exec/inp_to_exec.c\
exec/check_valid_command.c\
exec/fork_command.c\
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
hash/hash.c\
hash/hash_functions.c\
hash/init_hash.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB			=	$(words $(SRC_BASE))
INDEX		=	0

all :
	@make -C $(LIBFT_DIR)
	@make -j $(NAME)

$(NAME):		$(LIBFT_LIB) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(LIBS) \
		$(LIBFT_LIB) \
		$(FLAGS) $(D_FLAGS)
	@strip -x $@
	@printf "\r\033[48;5;15;38;5;25m✅  MAKE $(NAME)\033[0m\033[K\n"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB)))))
	@$(CC) $(FLAGS) $(D_FLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR)\
		-I $(LIBFT_INC)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:			cleanlib
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[38;5;202m✖ clean $(NAME).\033[0m\033[K\n"

cleanlib:
	@make -C $(LIBFT_DIR) clean

fclean:			clean fcleanlib
	@rm -f $(NAME)
	@printf "\r\033[38;5;196m ❌ fclean $(NAME).\033[0m\033[K\n"

fcleanlib:		cleanlib
	@make -C $(LIBFT_DIR) fclean

re:				fclean all

relib:			fcleanlib $(LIBFT_LIB)

.PHONY :		fclean clean re relib cleanlib fcleanlib

-include $(OBJS:.o=.d)
