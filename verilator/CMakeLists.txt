#========================================================#
# led
#========================================================#
add_executable(Vled sim_led.cpp)
verilate(Vled 
    SOURCES ../rtl/perips/led.sv
    TOP_MODULE
    TRACE
)
set_target_properties(Vled PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)



#========================================================#
# uart
#========================================================#
add_executable(Vuart sim_uart.cpp)
set(UART_FILES ../rtl/perips/uart_top.sv ../rtl/perips/uart_rx.sv ../rtl/perips/uart_tx.sv)
verilate(Vuart SOURCES 
    ${UART_FILES}
    TOP_MODULE uart_test
    TRACE
    PREFIX Vuart
    VERILATOR_ARGS -Wno-WIDTHTRUNC -Wno-WIDTHEXPAND -Wno-CASEINCOMPLETE -Wno-COMBDLY -Wno-UNSIGNED  -Wno-UNOPTFLAT
    )
set_target_properties(Vuart PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)





#/usr/local/share/verilator/verilator-config.cmake
#========================================================#
# cpu core
#========================================================#
file(GLOB_RECURSE CPU_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../rtl/core/*.sv)

add_executable(Vcore sim_core.cpp)

# change target flag
verilate(Vcore
    SOURCES  ${CPU_FILES} 
    TOP_MODULE core
    PREFIX Vcore
    TRACE
    COVERAGE
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../rtl/core
    THREADS 8
    VERILATOR_ARGS -Wno-WIDTHTRUNC -Wno-WIDTHEXPAND -Wno-CASEINCOMPLETE -Wno-COMBDLY -Wno-UNSIGNED  -Wno-UNOPTFLAT
)

set_target_properties(Vcore PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)

