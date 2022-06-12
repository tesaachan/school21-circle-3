NAME		=	philo

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

M_DIR		=	philo
M_SRC		=	main.c philo_utils.c general.c philo_actions.c simulation.c

M_OBJ		=	$(M_SRC:.c=.o)

%.o:		%.c
				$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(M_OBJ)
				$(CC) $(M_OBJ) -lpthread -o ./$(NAME)

all:		$(NAME)

clean:
				@rm -rf $(M_OBJ)

fclean:		clean
				@rm -rf $(NAME)
				
re:				fclean all

.PHONY:		all clean fclean bonus re
