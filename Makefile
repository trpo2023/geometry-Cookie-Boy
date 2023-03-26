NAME_APP = app

CFLAGS = -Wall -Werror
DEPSFLAGS = -MMD

OBJ_DIR = obj
BIN_DIR = bin
APP_DIR = src/app
LIB_DIR = src/libapp

APP_PATH = $(BIN_DIR)/$(NAME_APP)

APP_SRC = $(wildcard $(APP_DIR)/*.c) # ��� ����� � ����������� .c ����� ����� � ������� ����������
LIB_SRC = $(wildcard $(LIB_DIR)/*.c)
APP_OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(APP_SRC)) # �� .c �������� � .o, SRC - ����� ������ ������
LIB_OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(LIB_SRC))
APP_DEPS = $(patsubst $(APP_OBJ), $(OBJ_DIR)/%.d, $(APP_OBJ)) # �� .o �������� � .d
LIB_DEPS = $(patsubst $(LIB_OBJ), $(OBJ_DIR)/%.d, $(LIB_OBJ))

all: $(APP_PATH)

$(APP_PATH): $(LIB_OBJ) $(APP_OBJ)
	gcc $^ -o $@

$(OBJ_DIR)/%.o: %.c
#	$(warning I am here)
	gcc $(CFLAGS) $(DEPSFLAGS) -c $< -o $@

clean:
	rm $(APP_PATH) $(OBJ_DIR)/$(APP_DIR)/*.* $(OBJ_DIR)/$(LIB_DIR)/*.*

-include $(LIB_DEPS) $(APP_DEPS)

.PHONY: all clean