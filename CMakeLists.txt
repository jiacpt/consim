cmake_minimum_required(VERSION 3.16)

project(bitsf VERSION 1.0.0 LANGUAGES C CXX)
enable_testing()


#========================================================#
# Verilator                                              #
#========================================================#
add_definitions(-DVL_NO_LEGACY)
find_package(verilator REQUIRED)


#========================================================#
# CCache                                                 #
#========================================================#
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif(CCACHE_FOUND)


#========================================================#
# Others                                                 #
#========================================================#
add_subdirectory(verilator)
add_subdirectory(fpga)




