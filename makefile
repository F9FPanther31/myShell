
CC=g++ 
TARGET=myshell
DIRS=src
SRCS = $(wildcard $(DIRS)/*.cpp)
OBJS+=$(SRCS:%.cpp=%.o)

$(TARGET): $(OBJS)
	$(CC) $^ -o $(TARGET) -g

../%.o: $(DIRS)/%.cpp 
	$(CC) -c $^ -o $@ -g

.PHONY:
run: 
	clean $(TARGET)
	./$(TARGET)

.PHONY:
clean:
	rm -f $(DIRS)/*.o 