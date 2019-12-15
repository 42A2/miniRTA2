# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 03:24:21 by mbrunel           #+#    #+#              #
#    Updated: 2019/12/15 21:48:50 by mbrunel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_DIR = libs
INC_DIR = incs
SRC_DIR = srcs
OBJ_DIR = objs

CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
OFLAGS =	$(LIB_DIR)/$(LIBFT_DIR)/$(LIBFT) $(MLX) 
NAME =		miniRT

SRCS = 		main.c \
			vec_utils1.c \
			vec_utils2.c \
			vec_utils3.c \
			colors_utils.c \
			parser.c \
			parse_gets.c \
			parse_utils.c

OBJS =		$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
MLX_DIR = mlx
LIBFT_DIR = libft
MLX = libmlx.dylib
LIBFT = libft.a

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIB_DIR)/$(MLX_DIR)
			$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR)
			cp $(LIB_DIR)/$(MLX_DIR)/$(MLX)  .
			$(CC) $(OFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/* Makefile
			mkdir -p $(OBJ_DIR)/
			$(CC) $(CFLAGS) -c $< -o $@


all :	${NAME}

clean : 

			rm -rf $(OBJS) $(LIB_DIR)/$(LIBFT_DIR)/*/*.o $(LIB_DIR)/$(MLX_DIR)/*.o

fclean :clean
			rm -rf $(NAME) $(LIB_DIR)/$(MLX_DIR)/$(MLX) $(LIB_DIR)/$(LIBFT_DIR)/$(LIBFT) $(LIB_DIR)/$(LIBFT_DIR)/libc/libc.a $(MLX)

re :	fclean all

clean2 : 
	rm -rf $(NAME)

c : clean2 all
	./$(NAME) file.rt

