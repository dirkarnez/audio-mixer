cmake_minimum_required(VERSION 3.18)

project("audio-mixer")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# find_package(portaudio 19 EXACT REQUIRED) # PATHS "P:\\Downloads\\cpp-libraries\\portaudio\\build\\cmake\\portaudio")
find_package(SndFile 1.2.0 EXACT REQUIRED)

# IF(portaudio_FOUND)
#     message(STATUS "YES")
# ELSE()
#     message(STATUS "NO")
# ENDIF()

IF(SndFile_FOUND)
    message(STATUS "SndFile_FOUND: YES")
ELSE()
    message(STATUS "SndFile_FOUND: NO")
ENDIF()


add_executable(${PROJECT_NAME}
    "src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} SndFile::sndfile) # portaudio_static)
