SRC =	free_mem.c	game.c	initial.c	map.c	map1.c	moves.c	moves1.c	moves2.c	moves3.c	printing.c	valid.c	 level.c	enm1.c	getNext/get_next_line.c	getNext/get_next_line_utils.c

NAME = so_long

INC = Libft/libft.a

all: ${NAME}

${NAME}: ${SRC}
	@make -C ./Libft
	@cc -Wall -Wextra -Werror -lmlx -framework openGL -framework Appkit $^ enm.c ${INC} -o $@  -D MODE=0

clean:
	@make clean -C ./Libft

fclean: clean
	@make fclean -C ./Libft
	@rm -f ${NAME}

bonus: ${SRC}
	@make -C ./Libft
	@cc -Wall -Wextra -Werror -lmlx -framework openGL -framework Appkit $^ enm_bonus.c ${INC} -o ${NAME} -D MODE=1

re: fclean all

.PHONY: all clean fclean bonus re