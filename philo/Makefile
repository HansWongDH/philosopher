# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 18:02:33 by wding-ha          #+#    #+#              #
#    Updated: 2022/07/08 18:33:12 by wding-ha         ###   ########.fr        #
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
CFLAGS			= -Wall -Wextra -Werror -pthread
RM				= rm -f

##################
#PATH AND LIBRARY#
##################

INC				= -Iinclude
SRC_DIR			= srcs/

##############
#sSOURCE FILE#
##############

S_SRCS			= $(SRC_DIR)main.c $(SRC_DIR)philo_init.c $(SRC_DIR)struct_init.c $(SRC_DIR)philo_utils.c\
				$(SRC_DIR)mutex_remove.c $(SRC_DIR)philo_monitor.c $(SRC_DIR)philo_libs.c

OBJS			= $(S_SRCS:.c=.o)

##########
#COMMANDS#
##########

all:			$(NAME)

$(NAME):		$(OBJS)
	@$(CC) $(CFLAGS) $(INC) -o $(NAME) $(MAIN) $(OBJS) $(LIB)

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
clean:
	@$(RM) $(OBJS) $(B_OBJS)

fclean: clean
	@$(RM) $(NAME) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re