# Definition of variables
SRCS	= ll_create.cpp \
		ll_delete.cpp \
		ll_delete_all.cpp \
		ll_insert.cpp \
		ll_length.cpp \
		ll_print.cpp \
		ll_search.cpp \
		ll_test.cpp

OBJS	= ll_create.o \
		ll_delete.o \
		ll_delete_all.o \
		ll_insert.o \
		ll_length.o \
		ll_print.o \
		ll_search.o \
		ll_test.o


# Rules: 
# target: dependencies
#   command used to create the target
ll-test: $(OBJS) ll_cnode.h
	g++ -o ll-test $(OBJS)


# Utility 'makedepend' finds the .h dependencies automatically
depend:;	makedepend $(SRCS)
# DO NOT DELETE

ll_create.o: ll_cnode.h
ll_delete.o: ll_cnode.h
ll_delete_all.o: ll_cnode.h
ll_insert.o: ll_cnode.h
ll_length.o: ll_cnode.h
ll_print.o: ll_cnode.h
ll_search.o: ll_cnode.h
ll_test.o: ll_cnode.h
