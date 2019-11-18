# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 16:00:17 by niduches          #+#    #+#              #
#    Updated: 2019/11/18 18:15:43 by niduches         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

D_SRC	=	./src/
D_INC	=	./include/
D_LIB	=	./lib/

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

SRC = $(addprefix $(D_SRC),$(SRC_PATH))

NAME	=	cube3d

OBJ	=	$(SRC:%.c=$(BUILD_DIR)/%.o)

CFLAGS	=	-g -I$(D_INC) #-Wall -Wextra -Werror

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

bonus: lib options $(OBJ)
	@echo "  BUILD    $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all options lib clean fclean re bonus
