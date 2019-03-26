CC         = gcc
JAVAH      = javah
MYCFLAGS   = -c -Wall -fPIC $(EXTRA_CFLAGS) `pkg-config glib-2.0 atk-bridge-2.0 atk --libs`
MYLDFLAGS  = -fPIC -shared $(EXTRA_CFLAGS)
COPY       = cp -a

JNI_PLATFORM = linux
CLASSPATH  = target/classes
TARGET_SRC = target/native
TARGET_DIR = target
SO_PREFIX  = lib
SO_SUFFIX  = .so

INCLUDE    = -I $(TARGET_SRC) -I $(JAVA_HOME)/include/ -I $(JAVA_HOME)/include/$(JNI_PLATFORM) `pkg-config --cflags glib-2.0 atk atk-bridge-2.0`
SOURCES    = src/main/native/*
TARGET     = $(TARGET_SRC)
OBJECTS    = $(TARGET:.c=.o)

EXECUTABLE = $(SO_PREFIX)OpenJDKAccessBridge$(SO_SUFFIX)

MYCFLAGS   += `pkg-config --cflags gtk+-2.0 glib-2.0 atk atk-bridge-2.0`
MYCFLAGS   += `pkg-config gthread-2.0 --cflags `

MYLDFLAGS  += `pkg-config --libs gtk+-2.0 glib-2.0 atk atk-bridge-2.0`
MYLDFLAGS  += `pkg-config gthread-2.0 --libs`

.PHONY:
JNI_LIST = net.java.openjdk.internal.accessibility.AccessBridge net.java.openjdk.internal.accessibility.ATKWindowEventListener

$(JNI_LIST):
	$(JAVAH) -force -classpath $(CLASSPATH) -d $(TARGET_SRC) $(JNI_LIST)

all: $(JNI_LIST) init $(SOURCES) $(EXECUTABLE)

.PHONY:
init:
	$(COPY) $(SOURCES) $(TARGET)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS)/*.c -o $(TARGET_DIR)/$@ $(MYLDFLAGS) $(LDFLAGS) $(INCLUDE)

.c.o:
	$(CC) $(MYCFLAGS) $(CFLAGS) $(INCLUDE) $< -o $@

clean-lib:
	rm -f $(TARGET_DIR)/$(EXECUTABLE)
	
clean-obj:
	rm -f $(OBJECTS) $(TARGET)
	
clean: clean-obj clean-lib
	
