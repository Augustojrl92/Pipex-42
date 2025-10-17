# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurodrig <aurodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 09:30:09 by aurodrig          #+#    #+#              #
#    Updated: 2024/10/13 15:45:52 by aurodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 				pipex

NAME_BONUS = 		pipex_bonus

CC = 				gcc

CFLAGS =			-g3 -Wall -Werror -Wextra #-fsanitize=address -g

SRC_FILES =			src/pipex.c \
			 		src/pipex_utils.c \
					src/pipex_errors.c \
					src/pipex_children.c\
					Aux/aux_1.c \
					Aux/aux_2.c \
					Aux/aux_3.c \
					Aux/aux_4.c \
				
SRC_FILES_BONUS = 	bonus/src_bonus/pipex_bonus.c \
					bonus/src_bonus/pipex_children_bonus.c \
					bonus/src_bonus/pipex_utils_bonus.c \
					bonus/src_bonus/pipex_here_doc_bonus.c \
					bonus/src_bonus/pipex_errors_bonus.c	\
					bonus/Aux_bonus/aux_1_bonus.c \
					bonus/Aux_bonus/aux_2_bonus.c \
					bonus/Aux_bonus/aux_3_bonus.c \
					bonus/Aux_bonus/aux_4_bonus.c \
					bonus/Aux_bonus/aux_5_bonus.c \
					
INCLUDE = 			includes/pipex.h
INCLUDE_BONUS = 	bonus/includes_bonus/pipex_bonus.h

OBJS = $(SRC_FILES:.c=.o)

OBJS_BONUS = $(SRC_FILES_BONUS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
$(NAME_BONUS): $(OBJS_BONUS) $(INCLUDE_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)


fclean: clean
	rm -f $(NAME) 
	rm -f $(NAME_BONUS)


re: fclean all

bonus: $(NAME_BONUS)

.PHONY: all clean fclean re