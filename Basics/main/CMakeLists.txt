idf_component_register(SRCS "rgb.c" "hello_world_main.c" "bit.c"
                    PRIV_REQUIRES spi_flash
                    REQUIRES driver
                    INCLUDE_DIRS "include"
                    )
