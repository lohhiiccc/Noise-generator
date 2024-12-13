SRC_DIR = srcs/
SRCS= \
	$(SRC_DIR)main.cpp \
	$(SRC_DIR)windowManager/WindowManager.cpp

MAKEFLAGS += --no-print-directory

NAME = window

CC = c++
CFLAGS = -Wall -Wextra -Werror -g3
CPPFLAGS = -MMD -MP
BUILDDIR = build/
INCLUDEDIR = includes/
DEPENDENCIESDIR = $(BUILDDIR)dependencies/

OBJS = $(SRCS:$(SRC_DIR)%.cpp=$(BUILDDIR)%.o)
DEPS = $(SRCS:$(SRC_DIR)%.cpp=$(DEPENDENCIESDIR)%.d)

-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -Iincludes/ $(OBJS) -lX11 -o $(NAME)

$(BUILDDIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	@mkdir -p $(DEPENDENCIESDIR)$(@:$(BUILDDIR)%$(@F)=%)
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) $(CPPFLAGS) -c $< -o $@
	@mv $(@:%.o=%.d) $(DEPENDENCIESDIR)$(@:$(BUILDDIR)%.o=%.d)

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	@$(MAKE) all

.PHONY: all clean fclean re
.DEFAULT_GOAL := all