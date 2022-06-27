# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 12:40:19 by yobougre          #+#    #+#              #
#    Updated: 2022/05/13 12:28:31 by hrecolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= ft_atoi.c \
	  get_next_line.c\
	  ft_isprint.c\
	  ft_putchar_fd.c\
	  ft_striteri.c\
	  ft_strnstr.c\
	  ft_bzero.c\
	  ft_itoa.c\
	  ft_putendl_fd.c\
	  ft_strjoin.c\
	  ft_strrchr.c\
	  ft_calloc.c\
	  ft_memchr.c\
	  ft_putnbr_fd.c\
	  ft_strlcat.c\
	  ft_strtrim.c\
	  ft_isalnum.c\
	  ft_memcmp.c\
	  ft_putstr_fd.c\
	  ft_strlcpy.c\
	  ft_substr.c\
	  ft_isalpha.c\
	  ft_memcpy.c\
	  ft_split.c\
	  ft_tolower.c\
	  ft_isascii.c\
	  ft_memmove.c\
	  ft_strchr.c\
	  ft_strmapi.c\
	  ft_toupper.c\
	  ft_isdigit.c\
	  ft_memset.c\
	  ft_strdup.c\
	  ft_strncmp.c\
	  ft_lstnew.c\
	  ft_lstadd_back.c\
	  ft_lstadd_front.c\
	  ft_lstsize.c\
	  ft_lstlast.c\
	  ft_lstdelone.c\
	  ft_lstclear.c\
	  ft_lstiter.c\
	  ft_lstmap.c

OBJS=	${SRCS:.c=.o}
NAME=	libft.a
CC=		gcc
CFLAGS= -Wall -Wextra -Werror
RM=		rm -f

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
all: ${NAME}

${NAME} : ${OBJS}
				@ar -rcs ${NAME} ${OBJS}
clean:
		  @${RM} ${OBJS} 
fclean:	
		  @${RM} ${OBJS} ${NAME}

re:		 fclean all

.PHONY: all clean fclean re bonus


