################################################################################
#   ---------------------------   Makefile    --------------------------------
#
#   Author:     Chaumier Pierre-Victor <pvchaumier@uc.cl>
#   Comments:   to use the program :
#				make all -> if you have not changed anything or if it is the
#							first time you use it
#				make clean all -> to delete the previous build and make a new
#								  one
#				make clean -> to delete the previous build
#				and then the command ./example
#
################################################################################

# COMPILER
CC = gcc -std=c99
CFLAGS = -Wall

# BINARY NAME
EXEC = tarea2

# SOURCE FOLDER
SRC = src

# OBJECT DIRECTORY
OBJS_DIR = obj

# OBJECTS LIST
OBJS = \
./$(OBJS_DIR)/main.o \
./$(OBJS_DIR)/minheap.o \
./$(OBJS_DIR)/linkedlist.o \
./$(OBJS_DIR)/binarytree.o \
./$(OBJS_DIR)/dictionary.o \
./$(OBJS_DIR)/pixel.o \
./$(OBJS_DIR)/qdbmp.o \

# CREATE OBJ
CREATE_OBJ = \
$(OBJS_DIR) \
$(OBJS)

# ALL COMMAND
all: $(CREATE_OBJ)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# CREATE OBJS_DIR
$(OBJS_DIR):
	mkdir $(OBJS_DIR)

# ./$(OBJS_DIR)/main.o: ./$(SRC)/linkedlist.h

# CREATE OBJ
./$(OBJS_DIR)/%.o: ./$(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o ./$(OBJS_DIR)/$*.o

# CLEAN COMMAND
clean:
	rm -rf ./$(OBJS_DIR) $(EXEC) $(TEST)
