
px = ./X_Frame/
pt = ./Thread/
pf = ./FileOPer/
lop = ./OP_Layer/
lep = ./EP_Layer/
lfa = ./FA_Layer/

obj_X = $(pf)FileOPer.o $(px)RegExLib.o $(px)X_CmdTarget.o $(px)X_XMLParser.o $(px)tinyxml2.o
obj_thread = $(pt)Thread.o $(pt)MultiThread.o $(pt)FileThread.o
obj_EP = $(lep)LineEPer.o

FA_VeX: FA_VeX.o $(obj_X) $(obj_thread) $(obj_EP)
	g++ -o FA_VeX FA_VeX.o $(obj_X) $(obj_thread) $(obj_EP)

FA_VeX.o: FA_VeX.cpp
	g++ -c FA_VeX.cpp

RegExLib.o: $(px)RegExLib.h $(px)RegExLib.cpp
	g++ -c $(px)RegExLib.cpp

X_CmdTarget.o: $(px)X_CmdTarget.h $(px)X_CmdTarget.cpp
	g++ -c $(px)X_CmdTarget.cpp

X_XMLParser.o: $(px)X_XMLParser.h $(px)X_XMLParser.cpp
	g++ -c $(px)X_XMLParser.cpp

tinyxml2.o: $(px)tinyxml2.h $(px)tinyxml2.cpp
	g++ -c $(px)tinyxml2.cpp

Thread.o: $(pt)Thread.h $(pt)Thread.cpp
	g++ -c $(pt)Thread.cpp

MultiThread.o: $(pt)MultiThread.h $(pt)MultiThread.cpp
	g++ -c $(pt)MultiThread.cpp

FileThread.o: $(pt)FileThread.h $(pt)FileThread.cpp
	g++ -c $(pt)FileThread.cpp

FileOPer.o: $(pf)FileOPer.h $(pf)FileOPer.cpp
	g++ -c $(pf)FileOPer.cpp


LineEPer.o: $(lep)EP_Layer_DEF.h $(lep)LineEPer.h $(lep)LineEPer.cpp
	g++ -c $(lep)LineEPer.cpp

.PHONY:clean
clean:
	rm $(px)*.o $(pt)*.o $(pf)*.o $(lep)*.o *.o FA_VeX
