INC_DIR := ./
SRC_DIR := ./
CC := g++
CPPFLAGS := -g -Wno-deprecated
LIBS := -lpthread -lsqlite3
INC_FILE := $(addprefix -I, $(INC_DIR))
CPP_FILE := $(wildcard ./*.cpp)
OBJS := $(patsubst %.cpp, %.o, $(CPP_FILE))
objs := $(addsuffix /*.o, $(SRC_DIR))
TARGET := server
$(TARGET):$(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^ $(INC_FILE) $(LIBS)
%.o:%.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $< $(INC_FILE) $(LIBS)
object:
	@echo $(objs)
clean:
	rm -fr $(TARGET) $(OBJS)
clean_o:
	rm -fr $(OBJS)