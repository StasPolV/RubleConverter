add_library(GUI MainWidget.h MainWidget.cpp CurrencyDropdown.h
                CurrencyDropdown.cpp)

target_include_directories(GUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GUI PUBLIC Qt6::Core Qt6::Widgets)
