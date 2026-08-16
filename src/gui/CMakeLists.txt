add_library(
  GUI
  MainWidget.h
  MainWidget.cpp
  CurrencyDropdown.h
  CurrencyDropdown.cpp
  AmountInputWidget.h
  AmountInputWidget.cpp
  ScalableLineEdit.h
  ScalableLineEdit.cpp
  CurrencyExchangePanel.h
  CurrencyExchangePanel.cpp
  ScalableIconButton.h
  ScalableIconButton.cpp)

target_include_directories(GUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GUI PUBLIC Model Controller Qt6::Core Qt6::Widgets)
