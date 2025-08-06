
# -->┊( NAMES )
NAME	=	cube3D
LIBFT	=	./Inc/Libft/libft.a
MLX		=	./minilibx-linux/libmlx.a

# -->┊( COMMANDS AND FLAGS )
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
VAL		=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
#FDFLAGS	=	--track-fds=yes #--trace-children=yes
SUPP	=	--suppressions=readline.supp

# -->┊( DIRECTORIES )
SRC_DIR			=	Src
OBJS_DIR		=	Objs
CUBE3D_DIR		=	Cube3D
RENDER_DIR		= 	Render
PARSE_DIR		=	Parsing

# -->┊( SOURCES AND OBJS )
MAIN_C			=	cube3D_main.c

RENDER_MAIN_C	=	render_main.c
RENDER_FILES_C	=	hooks.c init.c draw_utils.c draw_map.c raycast.c player_move.c \
					key_handling.c mini_map.c

PARSE_MAIN_C	=	parsing_main.c
PARSE_FILES_C	=	checker_helper.c \
					cub_checker.c \
					map_checker.c \
					parse_init_cleaning.c \
					square_map.c \
					texture_checker.c

MAIN			=	$(addprefix	$(CUBE3D_DIR)/, $(MAIN_C))
RENDER_MAIN		=	$(addprefix	$(RENDER_DIR)/, $(RENDER_MAIN_C))
PARSE_MAIN		=	$(addprefix	$(PARSE_DIR)/, $(PARSE_MAIN_C))

OBJS_PARSE			=	$(addprefix $(OBJS_DIR)/, $(PARSE_FILES_C:.c=.o))
OBJS_RENDER			=	$(addprefix $(OBJS_DIR)/, $(RENDER_FILES_C:.c=.o))
OBJS_MAIN			=	$(addprefix $(OBJS_DIR)/, $(MAIN_C:.c=.o))
OBJS_MAIN_RENDER	=	$(addprefix $(OBJS_DIR)/, $(RENDER_MAIN_C:.c=.o))
OBJS_MAIN_PARSE		=	$(addprefix $(OBJS_DIR)/, $(PARSE_MAIN_C:.c=.o))

# -->┊( RULES )
all: $(NAME)

$(NAME): $(OBJS_MAIN) $(OBJS_RENDER) $(OBJS_PARSE) $(LIBFT) $(MLX)
	$(M_COMP)
	@$(CC) $(CFLAGS) $(OBJS_MAIN) $(OBJS_RENDER) $(OBJS_PARSE) $(LIBFT) $(MLX) -lm -lz -lXext -lX11 -o $(NAME)
	$(M_DONE)

$(OBJS_DIR)/%.o: $(SRC_DIR)/$(CUBE3D_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/$(RENDER_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRC_DIR)/$(PARSE_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(LIBFT):
	@make -C ./Inc/Libft -s

$(MLX):
	@make -C ./minilibx-linux -s

render: $(OBJS_MAIN_RENDER) $(OBJS_RENDER) $(LIBFT) $(MLX)
	$(M_COMP_E)
	@$(CC) $(CFLAGS) $(OBJS_MAIN_RENDER) $(OBJS_RENDER) $(LIBFT) $(MLX) -lm -lz -lXext -lX11 -o $(NAME)
	$(M_DONE)

parse: $(OBJS_MAIN_PARSE) $(OBJS_PARSE) $(LIBFT)
	$(M_COMP_P)
	@$(CC) $(CFLAGS) $(OBJS_MAIN_PARSE) $(OBJS_PARSE) $(LIBFT) -o $(NAME)
	$(M_DONE)

clean:
	@make clean -C ./Inc/Libft -s
	@make clean -C ./minilibx-linux -s
	$(M_REMOBJS)
	@rm -rf $(OBJS_DIR)
	$(M_DONE)

fclean: clean
	@rm -rf $(LIBFT)
	$(M_REM)
	@rm -rf $(NAME)
	$(M_DONE)
	
re: fclean all

rp: fclean parse

rn: fclean render

.PHONY: all clean fclean re bonus rn rp


# -->┊ ( MAIN TEST RULES )
#val: all
#	$(VAL) $(SUPP) ./cube3D

# -->┊( EXE TEST RULES )
#render: all
#	./cube3D

# -->┊( COSMETICS )

#->┊ normal colors
DEF	=	\e[0;39m
BLK	= 	\e[0;30m
BLU	=	\e[0;34m
GRN	=	\e[0;32m

#->┊ bold colors
BGRN	=	\e[1;32m
BWHT	=	\e[1;37m

#->┊ background colors
WHTB 	=	\e[47m

#->┊ messages
M_COMP		= @echo "$(BLK)-->┊$(GRN)  Compiling: $(DEF)$(BLK)$(WHTB) $(NAME) $(BLK)$(DEF)"
M_COMP_E	= @echo "$(BLK)-->┊$(GRN)  Compiling: $(DEF)$(BLK)$(WHTB) RENDER $(NAME) $(BLK)$(DEF)"
M_COMP_P	= @echo "$(BLK)-->┊$(GRN)  Compiling: $(DEF)$(BLK)$(WHTB) PARSE $(NAME) $(BLK)$(DEF)"
M_REM		= @echo "$(BLK)-->┊$(BLU)  Removing:  $(DEF)$(BLK)$(WHTB) $(NAME) $(BLK)$(DEF)"
M_REMOBJS	= @echo "$(BLK)-->┊$(BLU)  Removing: $(BWHT) $(NAME)/objs $(BLK)$(DEF)"
M_DONE		= @echo "$(BLK)-->┊$(BGRN)  DONE!!$(DEF)"
