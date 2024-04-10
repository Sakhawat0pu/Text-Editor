CC=g++
CFLAGS=-g -std=c++14
all: myeditor

myeditor: ECCommand.o ECConcreteObserver.o ECEditor.o ECTextViewImp.o ECEditorTest.o
	$(CC) $(CFLAGS) ECCommand.o ECConcreteObserver.o ECEditor.o ECTextViewImp.o ECEditorTest.o -o myeditor

ECCommand.o: ECCommand.cpp ECCommand.h
	$(CC) $(CFLAGS) -c ECCommand.cpp

ECTextViewImp.o: ECTextViewImp.cpp ECTextViewImp.h ECObserver.h
	$(CC) $(CFLAGS) -c ECTextViewImp.cpp

ECConcreteObserver.o: ECConcreteObserver.cpp ECConcreteObserver.h
	$(CC) $(CFLAGS) -c ECConcreteObserver.cpp

ECEditor.o: ECEditor.cpp ECEditor.h ECObserver.h
	$(CC) $(CFLAGS) -c ECEditor.cpp

ECEditorTest.o:	ECEditorTest.cpp ECObserver.h
	$(CC) $(CFLAGS) -c ECEditorTest.cpp

clean:
	rm -rf *.o myeditor
