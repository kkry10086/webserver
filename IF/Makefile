SRC = $(wildcard ./*.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))

test:$(OBJ)
	g++ $^ -o $@

%.o:%.cpp
	g++ -c $< -o $@

clean:
	rm -rf ./*.o
