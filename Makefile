NAME = RT

CC = gcc

FLAG = -g -Wall -Wextra -Werror -fsanitize=address

SRC = 	 main.c \
		 ./option/copy_elem.c \
		 ./option/set_system.c \
		 ./option/free.c \
		 ./parser/tag.c \
		 ./parser/take_para.c \
		 ./parser/check_para.c \
		 ./parser/take_para_vec_rgb.c \
		 ./parser/struct_para.c \
		 ./parser/check_para_obj.c \
		 ./parser/take_para2.c \
		 ./parser/test_struct_obj.c \
		 ./fill_img/check_img.c \
		 ./fill_img/draw_line_load.c \
		 ./fill_img/draw_average_color.c \
		 ./fill_img/intersect_obj.c \
		 ./fill_img/effects.c \
		 ./fill_img/inter_caps.c \
		 ./light/lighting.c \
		 ./sdl/window.c \
		 ./sdl/draw_in_img.c \
		 ./sdl/ui.c \
		 ./sdl/init_ui.c \
		 ./sdl/sdl_utils.c \
		 ./sdl/ui_info.c \
		 ./sdl/object_selection.c \
		 ./sdl/handle.c \
		 ./light/get_diff.c \
		 ./light/ref.c \
		 ./light/inter_ref.c \
		 ./textures/textures.c \
		 ./textures/perlin.c \
		 ./textures/perlin_setup.c \
		 ./textures/perlin_utils.c \

LIBFT_FLAG = -L ./libft -lft

O_FILES = $(SRC:.c=.o)

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(O_FILES)
	@make -C libft
	@echo  "\033[0;32mLibft successfully created\n------------------\033[0m"
	@echo " - Compiling $(NAME)..."
	@$(CC) $(FLAGS) $^ -o $(NAME) $(LIBFT_FLAG) `~/.brew/bin/sdl2-config --libs` -lSDL2_ttf
	@echo  "\033[0;32mRay Tracer successfully compiled\n👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽\033[0m"

jfortin: $(O_FILES)
	@make -C libft
	@echo  "\033[0;32mLibft successfully created\n------------------\033[0m"
	@echo " - Compiling $(NAME)..."
	@$(CC) $(FLAGS) $^ -o $(NAME) $(LIBFT_FLAG) `/usr/local/Cellar/sdl2/2.0.4/bin/sdl2-config --libs` -lSDL2_ttf
	@echo  "\033[0;32mRay Tracer successfully compiled\n👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽  👍🏽\033[0m"

linux: $(O_FILES)
	@make -C libft
	@echo  "\033[0;32mLibft successfully created\n------------------\033[0m"
	@echo " - Compiling $(NAME)..."
	@$(CC) $(FLAGS) $^ -o $(NAME) $(LIBFT_FLAG) `sdl2-config --libs` -lSDL2_ttf -lm
	@echo  "\033[0;32mRay Tracer successfully compiled\n\033[0m"

%.o:%.c
	@echo " - Creating $<..."
	@$(CC) $(FLAGS) `~/.brew/bin/sdl2-config --cflags` `sdl2-config --cflags` -I ~/.brew/opt/sdl2_ttf/include/SDL2/SDL_ttf.h -c $< -o $@

clean:
	@make -C libft clean
	@/bin/rm -f $(O_FILES)
	@echo "\033[0;31mObjects files successfully deleted\n------------------\033[0m"

fclean: clean
	@make -C libft fclean
	@/bin/rm -f $(NAME)
	@echo "\033[0;31mRay Tracer successfully deleted\n------------------\033[0m"

re: fclean all

re_linux: fclean linux

brew:
	curl -fsSL https://raw.githubusercontent.com/kube/42homebrewfix/master/install.sh > install.sh
	sh  install.sh
	bash
	brew install sdl2
	brew install sdl2_ttf
	zsh
	rm install.sh
