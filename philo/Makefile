# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 18:02:33 by wding-ha          #+#    #+#              #
#    Updated: 2022/04/22 21:42:33 by wding-ha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###########
#FILE NAME#
###########

NAME			= philo

#######
#FLAGS#
#######

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -pthread -fsanitize=address -g3
RM				= rm -f

##################
#PATH AND LIBRARY#
##################

INC				= -Iinclude -I$(LIBFT_DIR)
LIBFT_DIR		= ../libs/libft
LIB				= -L$(LIBFT_DIR) -lft
SRC_DIR			= srcs/

##############
#sSOURCE FILE#
##############

S_SRCS			= $(SRC_DIR)main.c $(SRC_DIR)pthread_create.c $(SRC_DIR)build_info.c $(SRC_DIR)print_function.c\
				$(SRC_DIR)destroy_lock.c $(SRC_DIR)time.c $(SRC_DIR)check_death.c

OBJS			= $(S_SRCS:.c=.o)

##########
#COMMANDS#
##########

all:			$(NAME)

$(NAME):		$(OBJS)
	@make re -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INC) -o $(NAME) $(MAIN) $(OBJS) $(LIB)

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
clean:
	@$(RM) $(OBJS) $(B_OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME) $(B_NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re