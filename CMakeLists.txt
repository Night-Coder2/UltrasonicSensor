set(ULTRASONICSENOS_LIB .)

add_library(UltrasonicSensor
        UltrasonicSensor.cpp
        )

target_include_directories(UltrasonicSensor PUBLIC
        ${ULTRASONICSENOS_LIB}
        ${ULTRASONICSENOS_LIB}/include
        )

target_link_libraries(UltrasonicSensor pico_stdlib)