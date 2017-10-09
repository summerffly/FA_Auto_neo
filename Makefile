
px = ./X_Frame/
pt = ./Thread/
pf = ./FileOPer/

FA_VeX: FA_VeX.o $(pt)Thread.o $(pt)MultiThread.o $(pt)FileThread.o $(pf)FileOPer.o $(px)RegExLib.o $(px)X_CmdTarget.o
	g++ -o FA_VeX FA_VeX.o $(pt)Thread.o $(pt)MultiThread.o $(pt)FileThread.o $(pf)FileOPer.o $(px)RegExLib.o $(px)X_CmdTarget.o

FA_VeX.o: FA_VeX.cpp
	g++ -c FA_VeX.cpp

Thread.o: $(pt)Thread.h $(pt)Thread.cpp
	g++ -c $(pt)Thread.cpp

MultiThread.o: $(pt)MultiThread.h $(pt)MultiThread.cpp
	g++ -c $(pt)MultiThread.cpp

FileThread.o: $(pt)FileThread.h $(pt)FileThread.cpp
	g++ -c $(pt)FileThread.cpp

FileOPer.o: $(pf)FileOPer.h $(pf)FileOPer.cpp
	g++ -c $(pf)FileOPer.cpp

RegExLib.o: $(px)RegExLib.h $(px)RegExLib.cpp
	g++ -c $(px)RegExLib.cpp

X_CmdTarget.o: $(px)X_CmdTarget.h $(px)X_CmdTarget.cpp
	g++ -c $(px)X_CmdTarget.cpp

.PHONY:clean
clean:
	rm $(px)*.o $(pt)*.o $(pf)*.o *.o FA_VeX
