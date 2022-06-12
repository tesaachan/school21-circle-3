NAME		=	philo_bonus

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

B_DIR		=	philo_bonus
B_SRC		=	main_bonus.c general_bonus.c philo_actions_bonus.c philo_utils_bonus.c simulation_bonus.c

B_OBJ		=	$(B_SRC:.c=.o)

%.o:		%.c
				$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(B_OBJ)
				$(CC) $(B_OBJ) -lpthread -o ./$(NAME)

all:		$(NAME)

clean:
				@rm -rf $(B_OBJ)

fclean:		clean
				@rm -rf $(NAME)
				
re:				fclean all

.PHONY:		all clean fclean bonus re
