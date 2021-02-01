# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 18:36:00 by cjaimes           #+#    #+#              #
#    Updated: 2021/02/01 21:41:12 by cjaimes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LIB_NAME	=	libft.a

LIB_DIR		=	libft

OBJ_DIR		=	obj/

SRC_DIR		=	srcs/

INCLUDE		=	includes

SRC			=	main.c \
				gnl_shell.c \
				main_2.c \
				parsing.c \
				parsing_2.c \
				utils.c \
				utils_2.c \
				utils_3.c \
				command.c \
				lexer/transitions_1.c \
				lexer/transitions_2.c \
				lexer/transitions_3.c \
				lexer/actions.c \
				lexer/actions_2.c \
				lexer/actions_3.c \
				tree/node.c \
				tree/node_2.c \
				tree/node_3.c \
				tree/node_4.c \
				tree/node_5.c \
				tree/execution.c \
				tree/exec.c \
				tree/pipe.c \
				tree/pipe_2.c \
				tree/redir.c \
				builtin/pwd.c \
				builtin/cd.c \
				builtin/env.c \
				builtin/env_2.c \
				builtin/exit.c \
				builtin/export.c \
				builtin/unset.c \
				builtin/echo.c
				

SRCS		=	${addprefix ${SRC_DIR}, ${SRC}}

OBJS		=	${patsubst ${SRC_DIR}%.c,${OBJ_DIR}%.o,${SRCS}}

NAME		=	minishell

RM			=	rm -f

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -g -O3

T		=	$(words ${OBJS})
N		=	0
C		=	$(words $N)${eval N := X $N}
_CYAN	=	\033[36m
_GREEN	=	\033[32m
ECHO	=	"[`expr $C  '*' 100 / $T`%]"

all:	${NAME}

${OBJ_DIR}%.o :	${SRC_DIR}%.c
			@mkdir -p ${OBJ_DIR}
			@mkdir -p ${OBJ_DIR}/builtin
			@mkdir -p ${OBJ_DIR}/tree
			@mkdir -p ${OBJ_DIR}/lexer
			@${CC} ${CFLAGS} -I ${INCLUDE} -I ${LIB_DIR}/includes -c $< -o $@
			@printf "%-60b\r" "${_CYAN}${ECHO}${_CYAN} Compiling $@"

${NAME}: ${OBJS}
	${MAKE} -C ${LIB_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}  -L${LIB_DIR} -lft

run : all
	./${NAME}

bonus: all

clean:
	${RM} ${OBJS}
	${MAKE} -C ${LIB_DIR} clean

fclean:	clean
	${RM} ${NAME}
	${RM} ${LIB_DIR}/${LIB_NAME}

re: fclean all