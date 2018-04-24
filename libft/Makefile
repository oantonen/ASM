NAME := libftprintf.a

LIBFT := ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
ft_toupper.c ft_tolower.c ft_isprint.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_putnstr.c ft_itoa_base.c ft_nbrlen.c \
ft_strrev.c ft_atoi_base.c ft_list_push_back.c ft_strchrlen.c get_next_line.c ft_abs.c

PRINTF := ft_printf.c pf_putchar.c pf_putstr.c pf_putaddr.c pf_put_signed_nb.c  pf_support.c pf_put_unsigned_nb.c \
pf_flag_mng.c pf_percent.c pf_put_float_f.c pf_float_support.c 

SRCSLIBFT := $(addprefix src_libft/,$(LIBFT))

SRCSPRINTF := $(addprefix src_printf/,$(PRINTF))

SRCS := $(SRCSLIBFT) $(SRCSPRINTF)

OBJS := $(SRCS:.c=.o)

HEADERS := ./includes

CFLAGS := -Wall -Wextra -Werror

all: $(NAME) 

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo "Lib is ready, my Lord"

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $< -I $(HEADERS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@echo "Clearing all"

re: fclean all
