OBJS = test.o
CC = g++
CXXFLAGS = -std=c++11

target : examples shared_application

$(TARGET):$(OBJS) $(HEADERS)
	@echo TARGET:$@
	@echo OBJECTS:$^
	$(CC) -o $@ $(CXXFLAGS) $^

clean:
	rm -rf $(TARGET) $(OBJS)
