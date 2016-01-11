NATIVE_JAVA_CLASSES = \
	com.cruzdb.Log

NATIVE_INCLUDE = ./include

ARCH := $(shell getconf LONG_BIT)
ZLOG_JAR = zlogjni-linux$(ARCH).jar

MAIN_SRC = src/main/java
OUTPUT = target
MAIN_CLASSES = $(OUTPUT)/classes

java:
	mkdir -p $(MAIN_CLASSES)
	javac -d $(MAIN_CLASSES) $(MAIN_SRC)/com/cruzdb/*.java
	javah -cp $(MAIN_CLASSES) -d $(NATIVE_INCLUDE) -jni $(NATIVE_JAVA_CLASSES)
