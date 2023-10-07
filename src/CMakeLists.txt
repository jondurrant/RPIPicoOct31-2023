add_executable(${NAME}
        main.cpp
       
        Agent.cpp
        GPIOInputMgr.cpp
        GPIOObserver.cpp
        
        HCSR04Range.cpp
        RangeArray.cpp
        Eyes.cpp
        Servo.cpp
        Head.cpp
       
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${NAME} 
	 pico_stdlib
     FreeRTOS-Kernel-Heap4 # FreeRTOS kernel and dynamic heap
     FREERTOS_PORT
     hardware_pwm
	)
	
target_include_directories(${NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
     )
     
# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})

# enable usb output, disable uart output
pico_enable_stdio_usb(${NAME} 0)
pico_enable_stdio_uart(${NAME} 1)
target_compile_definitions(${NAME} PRIVATE
    PICO_DEFAULT_UART_RX_PIN=16
    PICO_DEFAULT_UART_TX_PIN=17
)