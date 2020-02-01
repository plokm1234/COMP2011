SRCS	= $(shell /bin/ls mystring_*.cpp)
OBJS	= $(SRCS:.cpp=.o)
PROGS	= mystring


$(PROGS): $(OBJS)
	g++ -std=c++11 -o $@ $(OBJS)

$(SRCS):	mystring.h


%.o: %.cpp
	g++ -std=c++11 -c $< -o $@




clean:
	/bin/rm -f $(PROGS) $(OBJS) *~
