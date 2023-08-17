#========================================================#
# led
#========================================================#
add_executable(Vled sim_led.cpp)
verilate(Vled SOURCES  ../rtl/led.v TOP_MODULE TRACE )
set_target_properties(Vled PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)



#========================================================#
# uart
#========================================================#
# add_executable(Vuart sim_uart.cpp)
# set(UART_FILES ../rtl/uart_top.v ../rtl/uart_rx.v ../rtl/uart_tx.v)
# verilate(Vuart SOURCES  ${UART_FILES} TOP_MODULE  TRACE  PREFIX Vuart)
# set_target_properties(Vuart PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)



#/usr/local/share/verilator/verilator-config.cmake
#========================================================#
# cpu core
#========================================================#
file(GLOB_RECURSE CPU_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../rtl/core/*.v)

add_executable(Vcore sim_core.cpp)


# change target flag
verilate(Vcore
    SOURCES  ${CPU_FILES} 
    TOP_MODULE core
    PREFIX Vcore 
    TRACE
    COVERAGE
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../rtl/core
    THREADS 16
    VERILATOR_ARGS -Wno-WIDTHTRUNC -Wno-WIDTHEXPAND -Wno-CASEINCOMPLETE -Wno-COMBDLY -Wno-UNSIGNED  -Wno-UNOPTFLAT
)

set_target_properties(Vcore PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)

