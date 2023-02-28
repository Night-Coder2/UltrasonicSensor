set(ULTRASONICSENSOR_LIB .)

add_library(UltrasonicSensor
        UltrasonicSensor.cpp
        )

target_include_directories(UltrasonicSensor PUBLIC
        ${ULTRASONICSENSOR_LIB}
        ${ULTRASONICSENSOR_LIB}/include
        )

target_link_libraries(UltrasonicSensor pico_stdlib)