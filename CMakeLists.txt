cmake_minimum_required(VERSION 3.26)
project(Ai_Compiler LANGUAGES CXX)

# Standartları belirleyelim
set(CMAKE_CXX_STANDARD 17)

# Qt otomatik işlemlerini aç
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt6 paketlerini bul
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Tüm kaynak dosyalarını tek bir add_executable içerisine ekle
add_executable(Ai_Compiler
        main.cpp
        window.cpp
        window.h
        window.ui
        custom_text_edit.cpp
        custom_text_edit.h
        arrange_strings.cpp
        arrange_strings.h
        methods.cpp
        methods.h
        ai_model.cpp
        ai_model.h
        matrix.cpp
        matrix.h
        Models_Matrices.cpp
        Models_Matrices.h
        math.cpp
        math.h
)

# Qt kütüphanelerini bağla
target_link_libraries(Ai_Compiler
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

# Windows için Qt DLL'lerini otomatik kopyalama
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX "")
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif()

    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif()
    endif()

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET Ai_Compiler POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:Ai_Compiler>/plugins/platforms/")
        add_custom_command(TARGET Ai_Compiler POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:Ai_Compiler>/plugins/platforms/")
    endif()

    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET Ai_Compiler POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:Ai_Compiler>")
    endforeach()
endif()
