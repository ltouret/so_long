# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 13:00:20 by ltouret           #+#    #+#              #
#    Updated: 2021/09/07 21:49:52 by ltouret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS = srcs/main.c srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

FSAN = -fsanitize=address

MATH_FLAGS	= -lm

MLX_FLAGS	= -Lmlx/ -lmlx -lXext -lX11 -lbsd

LIBFT_FLAGS	= #-Llibft -lft

INCLUDES	= -I mlx #-I libft

.c.o:
		${CC} ${INCLUDES} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		#make -C libft/ 
		make -C mlx/
		${CC} ${OBJS} ${LIBFT_FLAGS} ${MATH_FLAGS} ${MLX_FLAGS} -o ${NAME} 

all:	${NAME}

clean:
		#make -C libft clean
		make -C mlx clean                                                       
		${RM} ${OBJS}

fclean:	clean
		#make -C libft/ fclean
		${RM} ${NAME}

re:		fclean all

test:	all
		./$(NAME) maps/file.ber

.PHONY: all clean fclean re test
