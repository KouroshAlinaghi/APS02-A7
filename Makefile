C_FLAGS=-std=c++11 -Wall -Wextra
SRC_DIR=src
SRCS=$(wildcard ${SRC_DIR}/*.cpp)
HEADERS=$(wildcard ${SRC_DIR}/*.hpp)
OBJS=$(subst .cpp,.o,$(SRCS))

A7: $(OBJS)
	g++ $(OBJS) -o futballFantasy.out

%.o: %.cpp $(HEADERS)
	g++ $(C_FLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS)
