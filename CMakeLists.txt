cmake_minimum_required(VERSION 3.5)
project(EmbedResource)

set(CMAKE_CXX_STANDARD 17)

add_executable(embed-resource embedresource.cpp)

function(embed_resources out_var)
    set(result)
    foreach(in_f ${ARGN})

        #message("ARGN: ${ARGN}")
        #message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
        #message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
        #message("in_f: ${in_f}")
        #get_filename_component(current_file_path ${in_f} DIRECTORY)

        file(RELATIVE_PATH rel_f ${CMAKE_SOURCE_DIR} ${in_f})
        #message("rel_f: ${rel_f}")

        #get_filename_component(current_file_name ${in_f} NAME)
        #message("current_file_name: ${current_file_name}")
        set(out_f "${PROJECT_BINARY_DIR}/resources/${rel_f}.cpp")
        #message("out_f: ${out_f}")

        add_custom_command(
            OUTPUT ${out_f}
            COMMAND embed-resource ${out_f} ${rel_f}
            DEPENDS ${in_f}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Building binary file for embedding ${out_f}"
            VERBATIM
        )
        list(APPEND result "${out_f}")
    endforeach()
    set(${out_var} "${result}" PARENT_SCOPE)
endfunction()

#find_package(Boost COMPONENTS filesystem REQUIRED)
#target_link_libraries(embed-resource ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

#set(EMBED_RES_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
