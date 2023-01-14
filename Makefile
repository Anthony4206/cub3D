# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 13:11:44 by alevasse          #+#    #+#              #
#    Updated: 2023/01/10 09:29:35 by alevasse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= cub3D

SRC				=	src/main.c src/utils.c src/init.c src/parse/parse.c src/parse/parse_map.c \
					src/parse/parse_map_utils.c src/parse/parse_header.c src/parse/parse_header_utils.c \
					src/parse/parse_wall.c src/parse/parse_wall_utils.c src/parse/parse_utils.c\
					src/draw/draw.c src/draw/draw_utils.c src/draw/draw_walls_w_tex.c src/draw/raycaster_walls.c \
					src/draw/key_events.c src/draw/mouse_events.c\

SRC_B			= 

OBJ 			= ${SRC:.c=.o}
OBJ_B			= ${SRC_B:.c=.o}

INCLUDE 		= -I./include/ -Imlx

MLX				= -Lmlx -lmlx -framework OpenGL -framework AppKit

HEAD			= include/libft.h

LIBS 			= ./libft/
				
CC 				= gcc -g 
CFLAGS 			= -Wall -Wextra -Werror #-fsanitize=address

AR 				= ar rcs
RM 				= rm -f

GREEN			:= "\033[0;32m"
CYAN			:= "\033[0;36m"
RESET			:= "\033[0m"

%.o:			%.c
				@${CC} ${CFLAGS} ${INCLUDE} -o $@ -c $<

all: 			${NAME}

bonus:			${OBJ_B} ${HEAD}
				@make all -C ${LIBS}
				@echo ${GREEN}"Successfully updated 'libft'" ${RESET}
				@${CC} ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJ_B} ${LIBS}libft.a
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}
				@touch bonus

${NAME}:		${OBJ} ${HEAD}
				@make all -C ${LIBS}
				@echo ${GREEN}"Successfully updated 'libft'" ${RESET}
				@${CC} ${CFLAGS} ${INCLUDE} ${MLX} -o ${NAME} ${OBJ} ${LIBS}libft.a
				@echo ${GREEN}"Compiled '${NAME}' with success" ${RESET}

clean:
				@make clean -C ${LIBS}
				@${RM} ${OBJ}
#				@${RM} bonus
				@echo ${CYAN}"Cleaned '${NAME}' objects with success"${RESET}
				
fclean:			clean
				@make fclean -C ${LIBS}
				@${RM} ${NAME}
				@echo ${CYAN}"Removed '${NAME}' with success"${RESET}

re:				fclean all

.PHONY: 		all clean fclean re