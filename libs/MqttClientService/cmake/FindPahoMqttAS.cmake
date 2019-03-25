find_path(PahoMqttAS_INCLUDE_DIR
    NAMES MQTTClient.h
)
find_library(PahoMqttAS_LIBRARY
    NAMES paho-mqtt3as
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(PahoMqttAS
    DEFAULT_MSG
    PahoMqttAS_INCLUDE_DIR PahoMqttAS_LIBRARY
)

if(PahoMqttAS_FOUND AND NOT TARGET PahoMqttAS::PahoMqttAS)
    add_library(PahoMqttAS::PahoMqttAS UNKNOWN IMPORTED)
    set_target_properties(PahoMqttAS::PahoMqttAS PROPERTIES
        IMPORTED_LOCATION "${PahoMqttAS_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${PahoMqttAS_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(PahoMqttAS_INCLUDE_DIR PahoMqttAS_LIBRARY)
