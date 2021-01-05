# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
include_directories(cpp/glm cpp/Include/ )



set(BULLET_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/")

#set(ASSIMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/Assimp_libs/cmake/debug/")

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        cpp/native-lib.cpp cpp/Engine.cpp cpp/Scene/Scene.cpp cpp/OpenGL/OpenGLMesh.cpp cpp/Loader/SceneLoader.cpp cpp/Object/Object.cpp cpp/OpenGL/Material.cpp cpp/Animation/AnimationData.cpp cpp/Animation/Animation.cpp cpp/Inputs/Touch.cpp cpp/OpenGL/OpenGLTexture.cpp cpp/Physics/PhysicsManager.cpp cpp/Gui/Button.cpp cpp/Gui/Gui.cpp)
add_library(bullet_lib STATIC IMPORTED)

set_target_properties(bullet_lib PROPERTIES IMPORTED_LOCATION
        ${BULLET_LIB_DIR}/${ANDROID_ABI}/libBullet.a)

message(STATUS "path: ${bullet_lib}")


find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib

        android
        EGL
        log
        #GLESv2
        GLESv3

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        bullet_lib

        )

#add_library(assimp SHARED IMPORTED)
#set_property(TARGET assimp PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/Assimp_libs/cmake/debug/${ANDROID_ABI}/libassimpd.so)
#target_include_directories(${sample} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cpp/assimp)
#target_link_libraries(${sample} assimp)
#add_custom_command(TARGET ${sample} POST_BUILD
      #  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/libs/Assimp_libs/cmake/debug/${ANDROID_ABI}/libassimpd.so ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})