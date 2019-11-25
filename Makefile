# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 16:00:17 by niduches          #+#    #+#              #
#    Updated: 2019/11/25 09:58:50 by niduches         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

D_SRC		=	./src/
D_SRC_BONUS	=	$(D_SRC)bonus/
D_INC		=	./include/
D_LIB		=	./lib/

LIB_DIR_PATH	=	libft

LIB = $(addprefix $(D_LIB),$(LIB_DIR_PATH))

BUILD_DIR	=	build

SRC_PATH	=	main.c					\
				parsing.c				\
				get_arg.c				\
				get_map.c				\
				to_good_map.c			\
				good_map.c				\
				free_all.c				\
				init.c					\
				display.c				\
				raycasting.c			\
				draw.c					\
				get_sprite.c			\
				get_wall.c				\
				get_hit_raycasting.c	\
				sort_sprite.c			\
				display_sprite.c		\
				put_in_bmp.c			\

SRC = $(addprefix $(D_SRC),$(SRC_PATH))

SRC_PATH_BONUS	=	main_bonus.c				\
					parsing_bonus.c				\
					get_arg_bonus.c				\
					get_map_bonus.c				\
					to_good_map_bonus.c			\
					good_map_bonus.c			\
					free_all_bonus.c			\
					init_bonus.c				\
					display_bonus.c				\
					raycasting_bonus.c			\
					draw_bonus.c				\
					get_sprite_bonus.c			\
					get_wall_bonus.c			\
					get_hit_raycasting_bonus.c	\
					sort_sprite_bonus.c			\
					display_sprite_bonus.c		\
					put_in_bmp_bonus.c			\
					attack_bonus.c				\
					draw_floor_bonus.c			\
					display_map_bonus.c			\
					update_key_bonus.c			\
					key_bonus.c					\
					play_music_bonus.c			\

SRC_BONUS = $(addprefix $(D_SRC_BONUS),$(SRC_PATH_BONUS))

NAME	=	cube3d

OBJ			=	$(SRC:%.c=$(BUILD_DIR)/%.o)
OBJ_BONUS	=	$(SRC_BONUS:%.c=$(BUILD_DIR)/%.o)

CFLAGS	=	-I$(D_INC) -Wall -Wextra -Werror

LDFLAGS	=	-L$(D_LIB) -lm -lft -lmlx -framework OpenGL -framework Appkit

all:	$(NAME)

options:
	@echo "  CC       $(CC)"
	@echo "  CFLAGS   $(CFLAGS)"
	@echo "  LDFLAGS  $(LDFLAGS)"

$(BUILD_DIR)/%.o: %.c $(INC)
	@mkdir -p $(@D)
	@echo "  CC       $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIB) clean --no-print-directory
	@echo "  RM       $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@$(MAKE) -C $(LIB) fclean --no-print-directory
	@echo "  RM       $(NAME)"
	@rm -f $(NAME) *~

lib:
	echo $(LIB)
	@make -C $(LIB) --no-print-directory

$(NAME): lib options $(OBJ)
	@echo "  BUILD    $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

bonus: lib options $(OBJ_BONUS)
	@echo "  BUILD    $@"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BONUS) $(LDFLAGS)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all options lib clean fclean re bonus
