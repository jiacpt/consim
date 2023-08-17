# add custom target download

add_custom_target(
    gw_download_led
    COMMAND  openFPGALoader -b tangnano20k -f ${CMAKE_CURRENT_SOURCE_DIR}/gowin_tang_nano_20k/impl/pnr/blink_leda.fs
    DEPENDS
)








