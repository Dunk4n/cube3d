# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 16:00:17 by niduches          #+#    #+#              #
#    Updated: 2019/11/12 20:56:21 by niduches         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		= 	gcc

D_SRC	=	./src/
D_INC	=	./lib/minilibx_mms_20191025_beta/
D_LIB	=	./lib/minilibx_mms_20191025_beta/
BUILD_DIR	=	build

SRC_PATH	=	main.c

SRC = $(addprefix $(D_SRC),$(SRC_PATH))

NAME	=	cube3d

OBJ	=	$(SRC:%.c=$(BUILD_DIR)/%.o)

CFLAGS	=	-I$(D_INC) #-Wall -Wextra -Werror

LDFLAGS	=	-L$(D_LIB) -lm

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
	@echo "  RM       $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@$(MAKE) -C $(D_LIB) clean --no-print-directory
	@echo "  RM       $(NAME)"
	@rm -f $(NAME) *~

lib:
	@make -C $(D_LIB) --no-print-directory

$(NAME): lib options $(OBJ)
	@echo "  BUILD    $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all options lib clean fclean re
