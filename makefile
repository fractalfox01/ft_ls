NAME= ft_ls

SRC := $(addsuffix .c, src/main src/sort_utils src/time_sort_forward src/time_sort_reverse)

INC := $(addsuffix .h, includes/ft_ls includes/ft_printf includes/get_next_line includes/libft)

FLAGS= -Wall -Werror -Wextra

$(NAME):
	gcc -g $(FLAGS) libft.a $(SRC) -o ft_ls

all: $(NAME)

clean:
	rm ft_ls 2>/dev/null | echo "Gone"
	rm -rf ft_ls.dSYM/ 2>/dev/null | echo "Gone"

fclean: clean

re: fclean all

add:
	git add makefile $(SRC) $(INC)
	git status

push:
	git commit -m "auto push"
	git push
