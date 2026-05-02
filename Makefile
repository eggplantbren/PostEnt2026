# Put the directory above 'DNest4' into an environment variable
# called DNEST4_PATH for this to work.

CC = g++
CXXFLAGS = -std=c++20 -O3 -march=native -Wall -Wextra -pedantic -DNDEBUG
LIBS = -ldnest4 -lpthread
INCLUDE = -I . -I $(DNEST4_PATH) -I pybind11/include -I /usr/include/python3.12
LIBS = -L $(DNEST4_PATH)/DNest4/code

default:
	$(CXX) $(FLAGS) $(INCLUDE) -c Examples/Binomial.cpp
	$(CXX) $(FLAGS) $(INCLUDE) -c main.cpp
	$(CXX) -Wno-unused-variable -Wno-attributes -Wno-unused-parameter -DNO_THREADS $(FLAGS) $(INCLUDE) -c Examples/PythonModel.cpp
	$(CXX) -Wno-unused-variable -Wno-attributes -Wno-unused-parameter -DNO_THREADS $(FLAGS) $(INCLUDE) -c main_python.cpp
	$(CXX) $(LIBS) -o main main.o Binomial.o -ldnest4 -pthread
	$(CXX) $(LIBS) -o main_python main_python.o PythonModel.o -lpython3.12 -ldnest4 -pthread
	rm -f *.o
