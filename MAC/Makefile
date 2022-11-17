SRC = $(wildcard ./*.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))

test:$(OBJ)
	g++ $^ -o $@ -g

%.o:%.cpp
	g++ -c $< -o $@ -g

clean:
	rm -rf ./*.o
