cmake_minimum_required(VERSION 3.5)
project(EmbedResource)

set(CMAKE_CXX_STANDARD 17)

add_executable(embed-resource embedresource.cpp)

function(embed_resources out_var prefix_var)

    set(result)

    #message("ARGN: ${ARGN}")
    #message("ARGC: ${ARGC}")
    #message("ARGV: ${ARGV}")

    math(EXPR range_stop "${ARGC}-1")
    
    foreach(index RANGE 1 ${range_stop} 2)

        math(EXPR prefix_index "${index} + 1")

        get_filename_component(current_file_name ${ARGV${index}} NAME)

        set(out_f "${PROJECT_BINARY_DIR}/resources/${ARGV${prefix_index}}_${current_file_name}.cpp")

        add_custom_command(
            OUTPUT ${out_f}
            COMMAND embed-resource ${out_f} ${ARGV${index}}
            DEPENDS ${ARGV${index}}
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
