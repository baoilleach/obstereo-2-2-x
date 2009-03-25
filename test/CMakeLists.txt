
add_executable(roundtrip roundtrip.cpp)
target_link_libraries(roundtrip ${BABEL_LIBRARY})
install(TARGETS roundtrip
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib
)


  
add_executable(uniqueidtest uniqueidtest.cpp)
target_link_libraries(uniqueidtest ${BABEL_LIBRARY})

ENABLE_TESTING()

ADD_TEST(UniqueIdTest ${EXECUTABLE_OUTPUT_PATH}/uniqueidtest UniqueIdTest)

