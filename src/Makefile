CXX = g++
CXX_STD = -std=c++1z -O2 -Wall -Wextra -Werror

CXX_CFLAGS = ${CXX_STD}
CXX_LFLAGS = ${}
#============================================================

tensor : tensor_c
	@echo "---- Linking $< -----"
	${CXX} -w $<.o ${CXX_LFLAGS} -o $@.out
	-${RM} $<.o
	@echo "==============="

tensor_c : tensor_example.cpp
	@echo "--- Compiling $< ---"
	${CXX} -c $< ${CXX_CFLAGS} -o $@.o

######

clean:
	-@${RM} *.out *.gch *.o *.out
