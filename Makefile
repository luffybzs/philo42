# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarab <ayarab@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 02:38:31 by ayarab            #+#    #+#              #
#    Updated: 2024/12/17 04:59:49 by ayarab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c philo_parsing.c mini_lib.c\
		 
					
OBJS			= $(SRCS:.c=.o)

CC				= cc -g3
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= philo


all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
				$(RM) $(OBJS)
				make clean -s

fclean:			clean
				$(RM) $(NAME)
				make fclean -s

re:				fclean $(NAME)

%.o : %c
				$(CC) $(CFLAGS) -c $< -o $@
				
  
.PHONY:			all clean fclean re bonus