Lab4: scheduler.o
	g++ scheduler.o -o Lab4
scheduler.o: scheduler.cpp heap.h
	g++ -c scheduler.cpp
clean:
	rm *.o Lab4
