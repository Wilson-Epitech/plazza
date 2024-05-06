##
## PLAZZA PROJECT, 2024
## NTS
## File description:
## Makefile
##

CC = g++
CFLAGS = -Wall -Wextra -std=c++17
EXECUTABLE = plazza
SRC_DIR = src
INCLUDE_DIR = Includes

SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(SRCS:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
		rm -f $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re
