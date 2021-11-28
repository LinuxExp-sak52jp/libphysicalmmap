CC = $(PREFIX)gcc

TARGETLIB = libphysicalmmap
OBJ_DIR = .
SRC_DIR = .

OBJS = mapping.o
SRCS = $(OBJS:.o=.c)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<

$(TARGETLIB).so: $(OBJS:%.o=$(OBJ_DIR)/%.o)
	$(CC) -shared -fPIC -o $@ $^


