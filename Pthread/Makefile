test:wrap.o task.o taskList.h Pthread.o test.cpp
	g++ $^ -o $@
wrap.o:wrap.cpp 
	g++ -c $< -o $@
task.o:task.cpp
	g++ -c $< -o $@
Pthread.o:Pthread.cpp
	g++ -c $< -o $@
	
cleang:
	rm *.gch
clean:
	rm *.gch *.o *~ 
