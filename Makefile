
px = ./X_Frame/
pt = ./Thread/
lop = ./OP_Layer/
lep = ./EP_Layer/
lfa = ./FA_Layer/

obj_X = $(px)RegExLib.o $(px)X_Tool.o $(px)X_CmdTarget.o $(px)X_CFGLoader.o $(px)X_XMLParser.o $(px)tinyxml2.o
obj_thread = $(pt)Thread.o $(pt)MultiThread.o $(pt)FileThread.o
obj_OP = $(lop)FileOPer.o
obj_EP = $(lep)LineEPer.o $(lep)FileManager.o
obj_FA = $(lfa)FAitfX.o

FA_VeX: FA_VeX.o $(obj_X) $(obj_thread) $(obj_OP) $(obj_EP) $(obj_FA)
	g++ -o FA_VeX FA_VeX.o $(obj_X) $(obj_thread) $(obj_OP) $(obj_EP) $(obj_FA)

FA_VeX.o: FA_VeX.cpp
	g++ -c FA_VeX.cpp

RegExLib.o: $(px)RegExLib.h $(px)RegExLib.cpp
	g++ -c $(px)RegExLib.cpp

X_Tool.o: $(px)X_Tool.h $(px)X_Tool.cpp
	g++ -c $(px)X_Tool.cpp

X_CmdTarget.o: $(px)X_CmdTarget.h $(px)X_CmdTarget.cpp
	g++ -c $(px)X_CmdTarget.cpp

X_CFGLoader.o: $(px)X_CFGLoader.h $(px)X_CFGLoader.cpp
	g++ -c $(px)X_CFGLoader.cpp

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

FileOPer.o: $(lop)FileOPer.h $(lop)FileOPer.cpp
	g++ -c $(lop)FileOPer.cpp

LineEPer.o: $(lep)LineEPer.h $(lep)LineEPer.cpp
	g++ -c $(lep)LineEPer.cpp

FileManager.o: $(lep)FileManager.h $(lep)FileManager.cpp
	g++ -c $(lep)FileManager.cpp

FAitfX.o: $(lfa)FAitfX.h $(lfa)FAitfX.cpp
	g++ -c $(lfa)FAitfX.cpp

.PHONY:clean
clean:
	rm $(px)*.o $(pt)*.o $(lop)*.o $(lep)*.o $(lfa)*.o *.o FA_VeX
