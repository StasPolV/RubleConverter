add_library(Core CurrencyFetcher.h CurrencyFetcher.cpp)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Core PUBLIC Qt6::Core Qt6::Network)
