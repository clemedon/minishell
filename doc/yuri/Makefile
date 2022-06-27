# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 11:01:55 by hrecolet          #+#    #+#              #
#    Updated: 2022/06/01 14:32:17 by hrecolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	Minishell

SRCS 		=	srcs/main.c\
				srcs/utils/utils.c\
				srcs/pipes/error.c\
				srcs/pipes/ft_free.c\
				srcs/pipes/ft_split.c\
				srcs/pipes/ft_split_path.c\
				srcs/pipes/join.c\
				srcs/pipes/utils_both.c\
				srcs/pipes/utils_exec.c\
				srcs/pipes/utils_path.c\
				srcs/pipes/utils_pipe.c\
				srcs/pipes/utils_str.c\
				srcs/expand/env_expand.c\
				srcs/exec/exec_utils.c\
				srcs/exec/ft_echo.c\
				srcs/env/export.c\
				srcs/exec/is_builtin.c\
				srcs/parsing/count_token.c\
				srcs/parsing/parse_token.c\
				srcs/utils/error.c\
				srcs/parsing/token_check.c\
				srcs/exec/ft_split_space.c\
				srcs/dir/dir_prompt.c\
				srcs/utils/utils_2.c\
				srcs/parsing/ft_unquoting.c\
				srcs/exec/create_list.c\
				srcs/exec/utils_io.c\
				srcs/env/export_2.c\
				srcs/env/unset.c\
				srcs/env/utils_export.c\
				srcs/exec/clean_redirection.c\
				srcs/exec/open_io.c\
				srcs/exec/insert_file.c\
				srcs/exec/main_exec.c\
				srcs/expand/expand_utils.c\
				srcs/env/utils_error.c\
				srcs/env/utils_backslash.c\
				srcs/exit/exit.c\
				srcs/exec/open_io_utils.c\
				srcs/expand/expand_utils_2.c\
				srcs/utils_print.c\
				srcs/signal/signal.c\
				srcs/utils/utils_3.c\
				srcs/pipes/heredoc.c\
				srcs/utils/utils_4.c\
				srcs/parsing/count_token_2.c\
				srcs/parsing/parse_token_2.c\
				srcs/utils_main.c\
				srcs/refacto.c\
				srcs/utils_init.c\
				srcs/exit/exit_2.c\
				srcs/parsing/utils_token_check.c\
				srcs/dir/dir_error.c\
				srcs/env/utils_export_2.c\
				srcs/pipes/utils_heredoc.c\
				srcs/env/export_3.c\
				srcs/exec/utils_split_space.c\
				srcs/pipes/utils_heredoc_2.c

OBJS		=		$(SRCS:.c=.o)

INC		= 		includes/minishell.h\
				includes/struct.h\
				includes/includes.h\
				libft/libft.h

RM		=		rm -f

CC		=	gcc	

CFLAGS		=	-Wall -Wextra -Werror -g3

all:	$(NAME)

$(NAME): $(INC) $(OBJS)
	@clear
	@$(MAKE) -C libft
	@echo "Minishell : Libft compiled"
	@echo "\033[1;34m"
	@echo "Project name : $(NAME)"
	@echo "\n\033[1;32mOn going compilation... ⌛\033[0;m\n"
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME) -lreadline
	@make wait
	@echo "Bonne correction!"


norm:
	@echo "⚠️ \033[5;1;34m Checking The Norm \033[m⚠️"
	@if norminette $(SRCS) >/dev/null; then\
        echo "\033[1;32m    Norminette : OK\033[m";\
    else\
        echo "\033[1;31m    Norminette : Error\033[m";\
    fi
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C libft clean
	@echo "\033[1;31m ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣶⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣦⣄⣀⡀⣠⣾⡇⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⢿⣿⣿⡇⠀⠀⠀⠀"
	@echo "⠀⣶⣿⣦⣜⣿⣿⣿⡟⠻⣿⣿⣿⣿⣿⣿⣿⡿⢿⡏⣴⣺⣦⣙⣿⣷⣄⠀⠀⠀\033[1;34m Goodbye everyone\033[1;31m"
	@echo "⠀⣯⡇⣻⣿⣿⣿⣿⣷⣾⣿⣬⣥⣭⣽⣿⣿⣧⣼⡇⣯⣇⣹⣿⣿⣿⣿⣧⠀⠀"
	@echo "⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠸⣿⣿⣿⣿⣿⣿⣿⣷⠀\033[m"
	@echo "\033[1;1;32m♻️  Objects have been \033[5;1;31mdeleted\033[m ♻️"

fclean:
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@echo -n "\033[0;31m⠀"
	@echo "Uninstalling Minishell"
	@echo "[##############]"
	@echo "　╭━╮╭━╮ ╭╮ ╱ "　　
	@echo "　╰━┫╰━┫ ╰╯╱ ╭╮ "　　
	@echo "　╰━╯╰━╯　╱　╰╯" 　　　　　
	@echo "　     COMPLETE"
	@echo "\033[1;1;32m♻️  Objects and $(NAME) have been \033[5;1;31mdeleted\033[m ♻️"

wait:
	@echo -n "\r  5%  [\033[0;31m█\033[m.........................]"
	@sleep 0.1
	@clear
	@echo -n "\r 10%  [\033[0;31m███\033[m.......................]"
	@sleep 0.1
	@clear
	@echo -n "\r 15%  [\033[0;31m████\033[m......................]"
	@sleep 0.1
	@clear
	@echo -n "\r 20%  [\033[0;31m██████\033[m....................]"
	@sleep 0.1
	@clear
	@echo -n "\r 27%  [\033[0;31m████████\033[m..................]"
	@sleep 0.1
	@clear
	@echo -n "\r 32%  [\033[0;31m██████████\033[m................]"
	@sleep 0.1
	@clear
	@echo -n "\r 35%  [\033[0;31m███████████\033[m...............]"
	@sleep 0.1
	@clear
	@echo -n "\r 45%  [\033[0;31m█████████████\033[m.............]"
	@sleep 0.1
	@clear
	@echo -n "\r 50%  [\033[0;31m███████████████\033[m...........]"
	@sleep 0.1
	@clear
	@echo -n "\r 65%  [\033[0;31m██████████████████\033[m........]"
	@sleep 0.1
	@clear
	@echo -n "\r 80%  [\033[0;31m█████████████████████\033[m.....]"
	@sleep 0.1
	@clear
	@echo -n "\r 90%  [\033[0;31m████████████████████████\033[m..]"
	@sleep 0.1
	@clear
	@echo -n "\r 95%  [\033[0;31m█████████████████████████\033[m.]"
	@sleep 0.1
	@clear
	@echo -n "\r 99%  [\033[0;31m██████████████████████████\033[m]"
	@sleep 0.5
	@clear
	@echo -n "\r 100% [\033[0;32m██████████████████████████\033[m]\033[0;32m compilation terminee ✓\n\033[0;m"
re:		fclean all

.PHONY: all clean fclean re
