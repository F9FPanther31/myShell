.PHONY:all
CC=g++
TARGET=myshell
DIRS=../src
SRCS = $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))
OBJS=$(SRCS:%.cpp=%.o)

$(TARGET) : $(OBJS)
	$(CC) $^ -o $@ -g

%.o:%.cpp 
	$(CC) -c $< -o $@ -g

.PHONY:
clean:
	rm -f $(OBJS)


