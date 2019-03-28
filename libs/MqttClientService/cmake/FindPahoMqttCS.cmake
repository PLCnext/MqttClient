find_path(PahoMqttCS_INCLUDE_DIR
    NAMES MQTTClient.h
)
find_library(PahoMqttCS_LIBRARY
    NAMES paho-mqtt3cs
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(PahoMqttCS
    DEFAULT_MSG
    PahoMqttCS_INCLUDE_DIR PahoMqttCS_LIBRARY
)

if(PahoMqttCS_FOUND AND NOT TARGET PahoMqttCS::PahoMqttCS)
    add_library(PahoMqttCS::PahoMqttCS UNKNOWN IMPORTED)
    set_target_properties(PahoMqttCS::PahoMqttCS PROPERTIES
        IMPORTED_LOCATION "${PahoMqttCS_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${PahoMqttCS_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(PahoMqttCS_INCLUDE_DIR PahoMqttCS_LIBRARY)
