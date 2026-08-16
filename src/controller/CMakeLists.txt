add_library(Controller CurrencyFetcherController.h
                       CurrencyFetcherController.cpp)

target_include_directories(Controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Controller PUBLIC Core Model Qt6::Core)
