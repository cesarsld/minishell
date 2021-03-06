# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 14:55:10 by cjaimes           #+#    #+#              #
#    Updated: 2020/03/06 12:29:23 by cjaimes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT	=	./srcs/

HROOT	=	includes/

FILES	=	ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_putchar_bonus.c \
			ft_putstr_bonus.c \
			ft_putendl_bonus.c \
			ft_putnbr_bonus.c \
			ft_strcpy_bonus.c \
			ft_strncpy_bonus.c \
			ft_strcmp_bonus.c \
			ft_swap_bonus.c \
			ft_memalloc_bonus.c \
			ft_memdel_bonus.c \
			ft_strndup_bonus.c \
			ft_strcat_bonus.c \
			ft_strncat_bonus.c \
			ft_strstr_bonus.c \
			ft_isupper_bonus.c \
			ft_islower_bonus.c \
			ft_strnew_bonus.c \
			ft_strdel_bonus.c \
			ft_strclr_bonus.c \
			ft_striter_bonus.c \
			ft_striteri_bonus.c \
			ft_strmap_bonus.c \
			ft_strequ_bonus.c \
			ft_strnequ_bonus.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_printf/ft_printf.c \
			ft_printf/ft_itoa_base.c \
			ft_printf/utils.c \
			ft_printf/utils_2.c \
			ft_printf/handlers.c \
			ft_printf/flushers.c \
			ft_printf/safe_appends.c \
			ft_printf/flag_handlers.c \
			ft_printf/flag_handlers_2.c \
			ft_printf/flag_checkers.c \
			ft_printf/init.c

SRCS	=	$(addprefix ${ROOT}, ${FILES})

OBJS	=	${SRCS:.c=.o}

NAME	=	libft.a

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -I ${HROOT}

T		=	$(words ${OBJS})
N		=	0
C		=	$(words $N)${eval N := X $N}
_CYAN	=	\033[36m
_GREEN	=	\033[32m
ECHO	=	"[`expr $C  '*' 100 / $T`%]"

.PHONY:	fclean clean re


%.o :	%.c
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
		@printf "%-60b\r" "${_CYAN}${ECHO}${_CYAN} Compiling $@"

${NAME}:	${OBJS}
	@ar rcs ${NAME} ${OBJS}
	@printf "\r%b" "${_GREEN}Library ${NAME} compiled successfully! :D\n"
	

all:	${NAME}

bench:
	gcc ${CFLAGS} -shared -o libft.so -fPIC ${ROOT}ft_*.c

clean:
		@${RM} ${OBJS}

fclean:	clean
		@${RM} ${NAME}
		@${RM} libft.so

re:		fclean all
