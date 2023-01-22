# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 13:11:44 by alevasse          #+#    #+#              #
#    Updated: 2023/01/20 14:33:03 by alevasse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= cub3D

SRC				=	src/main.c src/utils.c src/init.c src/parse/parse.c src/parse/parse_map.c \
					src/parse/parse_map_utils.c src/parse/parse_header.c src/parse/parse_header_utils.c \
					src/parse/parse_wall.c src/parse/parse_wall_utils.c src/parse/parse_utils.c \
					src/draw/draw.c src/draw/draw_utils.c src/draw/draw_walls_w_tex.c src/draw/raycaster_walls.c \
					src/draw/key_events.c src/draw/move.c src/draw/move_sliding.c\

SRC_B			= 	bonus/main_bonus.c bonus/utils_bonus.c bonus/init_bonus.c bonus/parse/parse_bonus.c \
					bonus/parse/parse_map_bonus.c bonus/parse/parse_map_utils_bonus.c \
					bonus/parse/parse_header_bonus.c bonus/parse/parse_header_utils_bonus.c \
					bonus/parse/parse_wall_bonus.c bonus/parse/parse_wall_utils_bonus.c \
					bonus/parse/parse_utils_bonus.c bonus/draw/draw_bonus.c bonus/draw/draw_utils_bonus.c \
					bonus/draw/draw_walls_w_tex_bonus.c bonus/draw/raycaster_walls_bonus.c \
					bonus/draw/key_events_bonus.c bonus/draw/key_mouse_bonus.c bonus/minimap_bonus.c \
					bonus/draw/move_bonus.c bonus/init_door_bonus.c bonus/init_sprite_bonus.c \
					bonus/draw/sprite_calc_bonus.c bonus/draw/sprite_draw_bonus.c bonus/draw/raycaster_doors_bonus.c \
					bonus/minimap_utils_bonus.c bonus/draw/move_sliding_bonus.c \

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
				@${CC} ${CFLAGS} ${INCLUDE} ${MLX} -o ${NAME} ${OBJ_B} ${LIBS}libft.a
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
				@${RM} ${OBJ_B}
				@echo ${CYAN}"Cleaned '${NAME}' objects with success"${RESET}
				
fclean:			clean
				@make fclean -C ${LIBS}
				@${RM} ${NAME}
				@echo ${CYAN}"Removed '${NAME}' with success"${RESET}

re:				fclean all

.PHONY: 		all clean fclean re