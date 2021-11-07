
########################################
### Coded by 番茄
########################################

px = ./X_Frame/
lcmd = ./CMD_Handler/
lop = ./OP_Layer/
lep = ./EP_Layer/
lfa = ./FA_Layer/
las = ./AS_Layer/

ptest = ./neo_TEST/
pexe = ./../../FA/


obj_X = $(px)RegExLib.o $(px)X_Tool.o $(px)Xonfig.o $(px)Xonfig_Loader.o
obj_CMD = $(lcmd)DefCMD.o $(lcmd)CMD_Packet.o $(lcmd)CMD_Handler.o
obj_OP = $(lop)FileOPer.o
obj_EP = $(lep)LineEPer.o $(lep)FileManager.o
obj_FA = $(lfa)FAitfX.o
obj_AS = $(las)ASitfX.o


FA_Auto_neo: $(obj_X) $(obj_CMD) $(obj_OP) $(obj_EP) $(obj_FA) $(obj_AS) FA_Auto_neo.o
	g++ -o FA_Auto_neo $(obj_X) $(obj_CMD) $(obj_OP) $(obj_EP) $(obj_FA) $(obj_AS) FA_Auto_neo.o

FA_Auto_neo.o: FA_Auto_neo.cpp
	g++ -c FA_Auto_neo.cpp

RegExLib.o: $(px)RegExLib.h $(px)RegExLib.cpp
	g++ -c $(px)RegExLib.cpp

X_Tool.o: $(px)X_Tool.h $(px)X_Tool.cpp
	g++ -c $(px)X_Tool.cpp

Xonfig.o: $(px)Xonfig.h $(px)Xonfig.cpp
	g++ -c $(px)Xonfig.cpp

Xonfig_Loader.o: $(px)Xonfig_Loader.h $(px)Xonfig_Loader.cpp
	g++ -c $(px)Xonfig_Loader.cpp

DefCMD.o: $(lcmd)DefCMD.h $(lcmd)DefCMD.cpp
	g++ -c $(lcmd)DefCMD.cpp

CMD_Packet.o: $(lcmd)CMD_Packet.h $(lcmd)CMD_Packet.cpp
	g++ -c $(lcmd)CMD_Packet.cpp

CMD_Handler.o: $(lcmd)CMD_Handler.h $(lcmd)CMD_Handler.cpp
	g++ -c $(lcmd)CMD_Handler.cpp

FileOPer.o: $(lop)FileOPer.h $(lop)FileOPer.cpp
	g++ -c $(lop)FileOPer.cpp

LineEPer.o: $(lep)LineEPer.h $(lep)LineEPer.cpp
	g++ -c $(lep)LineEPer.cpp

FileManager.o: $(lep)FileManager.h $(lep)FileManager.cpp
	g++ -c $(lep)FileManager.cpp

FAitfX.o: $(lfa)FAitfX.h $(lfa)FAitfX.cpp
	g++ -c $(lfa)FAitfX.cpp

ASitfX.o: $(las)ASitfX.h $(las)ASitfX.cpp
	g++ -c $(las)ASitfX.cpp

.PHONY:clean
clean:
	rm $(px)*.o $(lcmd)*.o $(lop)*.o $(lep)*.o $(lfa)*.o $(las)*.o *.o FA_Auto_neo

test:
	rm $(ptest)FA_Auto_neo
	cp -f ./FA_Auto_neo $(ptest)FA_Auto_neo
	cp -f ./FA_Auto_neo.ini $(ptest)FA_Auto_neo.ini

install:
	rm $(pexe)FA_Auto_neo
	cp -f ./FA_Auto_neo $(pexe)FA_Auto_neo
	cp -f ./FA_Auto_neo.ini $(pexe)FA_Auto_neo.ini

########################################
