SOURCE_PATH = "../com/nana"
JFLAGS = -g
JC = javac
JVM= java 
# FILE=

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $(SOURCE_PATH)$*.java

CLASSES = \
	$(SOURCE_PATH)uLCDInterface.java

MAIN = com.nana.uLCDInterface 

default: classes


classes: $(CLASSES:.java=.class)

run: $(MAIN).class
	$(JVM) $(MAIN) $(FILE)

clean:
	$(RM) *.class
