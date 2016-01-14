set(java-sources
    com/cruzdb/Log.java
    com/cruzdb/NativeLibraryLoader.java
    com/cruzdb/ZObject.java
)
    
set(java-classes
    com/cruzdb/Log.class
    com/cruzdb/NativeLibraryLoader.class
    com/cruzdb/ZObject.class
)

set(jni-headers
    com_cruzdb_Log.h
)

set (source-tmp "")
foreach (source ${java-sources})
    list (APPEND source-tmp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/java/${source})
endforeach()
set(java-sources ${source-tmp})

add_custom_command(
    OUTPUT ${java-classes}
    COMMAND ${Java_JAVAC_EXECUTABLE}
    ARGS -d ${CMAKE_CURRENT_BINARY_DIR}
         ${java-sources}
    DEPENDS ${java-sources}
)

add_custom_command(
    OUTPUT ${jni-headers}
    COMMAND ${Java_JAVAH_EXECUTABLE}
    ARGS -verbose
         -classpath ${CMAKE_CURRENT_BINARY_DIR}
        -jni
         com.cruzdb.Log
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${java-classes}
)

list(APPEND sources native/zlogjni.cc)
list(APPEND sources ${jni-headers})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# jni.h jni_md.h
include_directories(${JAVA_INCLUDE_PATH})
include_directories(${JAVA_INCLUDE_PATH2})

add_library(zlogjni SHARED ${sources})
