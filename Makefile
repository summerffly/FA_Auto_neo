
FA_VeX: FA_VeX.o ./Thread/Thread.o ./Thread/MultiThread.o ./FileOPer/FileOPer.o
	g++ -o FA_VeX FA_VeX.o ./Thread/Thread.o ./Thread/MultiThread.o ./FileOPer/FileOPer.o

FA_VeX.o: FA_VeX.cpp
	g++ -c FA_VeX.cpp

Thread.o: ./Thread/Thread.cpp ./Thread/Thread.h
	g++ -c ./Thread/Thread.cpp

MultiThread.o: ./Thread/MultiThread.cpp ./Thread/MultiThread.h
	g++ -c ./Thread/MultiThread.cpp

FileOPer.o: ./FileOPer/FileOPer.cpp
	g++ -c ./FileOPer/FileOPer.cpp

.PHONY:clean
clean:
	rm ./Thread/*.o ./FileOPer/*.o *.o FA_VeX
