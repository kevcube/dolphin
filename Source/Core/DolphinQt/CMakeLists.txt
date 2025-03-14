if(POLICY CMP0084)
  # Disable trying to search for Qt3/4 if what we actually want is not found
  cmake_policy(SET CMP0084 NEW)
endif()

if (NOT QT_DIR AND MSVC)
  if(_M_ARM_64)
    set(QT_DIR "${CMAKE_SOURCE_DIR}/Externals/Qt/Qt6.3.0/ARM64/lib/cmake/Qt6")
  else()
    set(QT_DIR "${CMAKE_SOURCE_DIR}/Externals/Qt/Qt6.3.0/x64/lib/cmake/Qt6")
  endif()
endif()

set(CMAKE_AUTOMOC ON)

# For some reason the method in Qt6 documentation is not working (at least on ubuntu jammy)
# When Qt5 and Qt6 are given in same NAMES entry, only Qt5 is ever found.
find_package(QT NAMES Qt6 COMPONENTS Core Gui Widgets)
if(NOT QT_DIR)
  find_package(QT NAMES Qt5 COMPONENTS Core Gui Widgets)
endif()
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)
message(STATUS "Found Qt version ${QT_VERSION}")

set_property(TARGET Qt${QT_VERSION_MAJOR}::Core PROPERTY INTERFACE_COMPILE_FEATURES "")

add_executable(dolphin-emu
  AboutDialog.cpp
  AboutDialog.h
  CheatSearchFactoryWidget.cpp
  CheatSearchFactoryWidget.h
  CheatSearchWidget.cpp
  CheatSearchWidget.h
  CheatsManager.cpp
  CheatsManager.h
  ConvertDialog.cpp
  ConvertDialog.h
	CVarsWindow.cpp
	CVarsWindow.h
  DiscordHandler.cpp
  DiscordHandler.h
  DiscordJoinRequestDialog.cpp
  DiscordJoinRequestDialog.h
  FIFO/FIFOPlayerWindow.cpp
  FIFO/FIFOPlayerWindow.h
  FIFO/FIFOAnalyzer.cpp
  FIFO/FIFOAnalyzer.h
  Host.cpp
  Host.h
  HotkeyScheduler.cpp
  HotkeyScheduler.h
  Main.cpp
  MainWindow.cpp
  MainWindow.h
  MenuBar.cpp
  MenuBar.h
  NKitWarningDialog.cpp
  NKitWarningDialog.h
  RenderWidget.cpp
  RenderWidget.h
  Resources.cpp
  Resources.h
  SearchBar.cpp
  SearchBar.h
  Settings.cpp
  Settings.h
  ToolBar.cpp
  ToolBar.h
  Translation.cpp
  Translation.h
  WiiUpdate.cpp
  WiiUpdate.h
  Config/ARCodeWidget.cpp
  Config/ARCodeWidget.h
  Config/CheatCodeEditor.cpp
  Config/CheatCodeEditor.h
  Config/CheatWarningWidget.cpp
  Config/CheatWarningWidget.h
  Config/CommonControllersWidget.cpp
  Config/CommonControllersWidget.h
  Config/ControllerInterface/DualShockUDPClientAddServerDialog.cpp
  Config/ControllerInterface/DualShockUDPClientAddServerDialog.h
  Config/ControllerInterface/DualShockUDPClientWidget.cpp
  Config/ControllerInterface/DualShockUDPClientWidget.h
  Config/ControllerInterface/ControllerInterfaceWindow.cpp
  Config/ControllerInterface/ControllerInterfaceWindow.h
  Config/ControllerInterface/ServerStringValidator.cpp
  Config/ControllerInterface/ServerStringValidator.h
  Config/ControllersWindow.cpp
  Config/ControllersWindow.h
  Config/FilesystemWidget.cpp
  Config/FilesystemWidget.h
  Config/FreeLookWidget.cpp
  Config/FreeLookWidget.h
  Config/FreeLookWindow.cpp
  Config/FreeLookWindow.h
  Config/GamecubeControllersWidget.cpp
  Config/GamecubeControllersWidget.h
  Config/GameConfigEdit.cpp
  Config/GameConfigEdit.h
  Config/GameConfigHighlighter.cpp
  Config/GameConfigHighlighter.h
  Config/GameConfigWidget.cpp
  Config/GameConfigWidget.h
  Config/PrimeCheatsWidget.cpp
  Config/PrimeCheatsWidget.h
  Config/GeckoCodeWidget.cpp
  Config/GeckoCodeWidget.h
  Config/Graphics/AdvancedWidget.cpp
  Config/Graphics/AdvancedWidget.h
  Config/Graphics/BalloonTip.cpp
  Config/Graphics/BalloonTip.h
  Config/Graphics/EnhancementsWidget.cpp
  Config/Graphics/EnhancementsWidget.h
  Config/Graphics/GeneralWidget.cpp
  Config/Graphics/GeneralWidget.h
  Config/Graphics/GraphicsBool.cpp
  Config/Graphics/GraphicsBool.h
  Config/Graphics/GraphicsChoice.cpp
  Config/Graphics/GraphicsChoice.h
  Config/Graphics/GraphicsInteger.cpp
  Config/Graphics/GraphicsInteger.h
  Config/Graphics/GraphicsRadio.cpp
  Config/Graphics/GraphicsRadio.h
  Config/Graphics/GraphicsSlider.cpp
  Config/Graphics/GraphicsSlider.h
  Config/Graphics/GraphicsWidget.h
  Config/Graphics/GraphicsWindow.cpp
  Config/Graphics/GraphicsWindow.h
  Config/Graphics/HacksWidget.cpp
  Config/Graphics/HacksWidget.h
  Config/Graphics/PostProcessingConfigWindow.cpp
  Config/Graphics/PostProcessingConfigWindow.h
  Config/Graphics/SoftwareRendererWidget.cpp
  Config/Graphics/SoftwareRendererWidget.h
  Config/Graphics/PrimeWidget.cpp
  Config/Graphics/PrimeWidget.h
  Config/GraphicsModListWidget.cpp
  Config/GraphicsModListWidget.h
  Config/GraphicsModWarningWidget.cpp
  Config/GraphicsModWarningWidget.h
  Config/InfoWidget.cpp
  Config/InfoWidget.h
  Config/LogConfigWidget.cpp
  Config/LogConfigWidget.h
  Config/LogWidget.cpp
  Config/LogWidget.h
  Config/Mapping/FreeLookGeneral.cpp
  Config/Mapping/FreeLookGeneral.h
  Config/Mapping/FreeLookRotation.cpp
  Config/Mapping/FreeLookRotation.h
  Config/Mapping/GBAPadEmu.cpp
  Config/Mapping/GBAPadEmu.h
  Config/Mapping/GCKeyboardEmu.cpp
  Config/Mapping/GCKeyboardEmu.h
  Config/Mapping/GCMicrophone.cpp
  Config/Mapping/GCMicrophone.h
  Config/Mapping/GCPadEmu.cpp
  Config/Mapping/GCPadEmu.h
	Config/Mapping/GCPadEmuMetroid.cpp
  Config/Mapping/GCPadEmuMetroid.h
  Config/Mapping/GCPadWiiUConfigDialog.cpp
  Config/Mapping/GCPadWiiUConfigDialog.h
  Config/Mapping/Hotkey3D.cpp
  Config/Mapping/Hotkey3D.h
  Config/Mapping/HotkeyControllerProfile.cpp
  Config/Mapping/HotkeyControllerProfile.h
  Config/Mapping/HotkeyDebugging.cpp
  Config/Mapping/HotkeyDebugging.h
  Config/Mapping/HotkeyGBA.cpp
  Config/Mapping/HotkeyGBA.h
  Config/Mapping/HotkeyGeneral.cpp
  Config/Mapping/HotkeyGeneral.h
  Config/Mapping/HotkeyGraphics.cpp
  Config/Mapping/HotkeyGraphics.h
  Config/Mapping/HotkeyStates.cpp
  Config/Mapping/HotkeyStates.h
  Config/Mapping/HotkeyStatesOther.cpp
  Config/Mapping/HotkeyStatesOther.h
  Config/Mapping/HotkeyTAS.cpp
  Config/Mapping/HotkeyTAS.h
  Config/Mapping/HotkeyWii.cpp
  Config/Mapping/HotkeyWii.h
  Config/Mapping/IOWindow.cpp
  Config/Mapping/MappingButton.cpp
  Config/Mapping/MappingButton.h
  Config/Mapping/MappingCommon.cpp
  Config/Mapping/MappingCommon.h
  Config/Mapping/MappingIndicator.cpp
  Config/Mapping/MappingIndicator.h
  Config/Mapping/MappingNumeric.cpp
  Config/Mapping/MappingNumeric.h
  Config/Mapping/MappingWidget.cpp
  Config/Mapping/MappingWidget.h
  Config/Mapping/MappingWindow.cpp
  Config/Mapping/MappingWindow.h
  Config/Mapping/WiimoteEmuExtension.cpp
  Config/Mapping/WiimoteEmuExtension.h
  Config/Mapping/WiimoteEmuExtensionMotionInput.cpp
  Config/Mapping/WiimoteEmuExtensionMotionInput.h
  Config/Mapping/WiimoteEmuExtensionMotionSimulation.cpp
  Config/Mapping/WiimoteEmuExtensionMotionSimulation.h
  Config/Mapping/WiimoteEmuGeneral.cpp
  Config/Mapping/WiimoteEmuGeneral.h
  Config/Mapping/WiimoteEmuMetroid.cpp
  Config/Mapping/WiimoteEmuMetroid.h
  Config/Mapping/PrimeHackEmuWii.cpp
  Config/Mapping/PrimeHackEmuWii.h
  Config/Mapping/PrimeHackEmuGC.cpp
  Config/Mapping/PrimeHackEmuGC.h
  Config/Mapping/HotkeyPrimeHack.cpp
  Config/Mapping/HotkeyPrimeHack.h
  Config/Mapping/WiimoteEmuMotionControl.cpp
  Config/Mapping/WiimoteEmuMotionControl.h
  Config/Mapping/WiimoteEmuMotionControlIMU.cpp
  Config/Mapping/WiimoteEmuMotionControlIMU.h
  Config/NewPatchDialog.cpp
  Config/NewPatchDialog.h
  Config/PatchesWidget.cpp
  Config/PatchesWidget.h
  Config/PropertiesDialog.cpp
  Config/PropertiesDialog.h
  Config/SettingsWindow.cpp
  Config/SettingsWindow.h
  Config/ToolTipControls/ToolTipCheckBox.cpp
  Config/ToolTipControls/ToolTipCheckBox.h
  Config/ToolTipControls/ToolTipComboBox.cpp
  Config/ToolTipControls/ToolTipComboBox.h
  Config/ToolTipControls/ToolTipRadioButton.cpp
  Config/ToolTipControls/ToolTipRadioButton.h
  Config/ToolTipControls/ToolTipSlider.cpp
  Config/ToolTipControls/ToolTipSlider.h
  Config/ToolTipControls/ToolTipSpinBox.cpp
  Config/ToolTipControls/ToolTipSpinBox.h
  Config/ToolTipControls/ToolTipWidget.h
  Config/VerifyWidget.cpp
  Config/VerifyWidget.h
  Config/WiimoteControllersWidget.cpp
  Config/WiimoteControllersWidget.h
  Debugger/BreakpointWidget.cpp
  Debugger/BreakpointWidget.h
  Debugger/CodeDiffDialog.cpp
  Debugger/CodeDiffDialog.h
  Debugger/CodeViewWidget.cpp
  Debugger/CodeViewWidget.h
  Debugger/CodeWidget.cpp
  Debugger/CodeWidget.h
  Debugger/JITWidget.cpp
  Debugger/JITWidget.h
  Debugger/MemoryViewWidget.cpp
  Debugger/MemoryViewWidget.h
  Debugger/MemoryWidget.cpp
  Debugger/MemoryWidget.h
  Debugger/NetworkWidget.cpp
  Debugger/NetworkWidget.h
  Debugger/NewBreakpointDialog.cpp
  Debugger/NewBreakpointDialog.h
  Debugger/PatchInstructionDialog.cpp
  Debugger/PatchInstructionDialog.h
  Debugger/RegisterColumn.cpp
  Debugger/RegisterColumn.h
  Debugger/RegisterWidget.cpp
  Debugger/RegisterWidget.h
  Debugger/ThreadWidget.cpp
  Debugger/ThreadWidget.h
  Debugger/WatchWidget.cpp
  Debugger/WatchWidget.h
  GameList/GameList.cpp
  GameList/GameList.h
  GameList/GameListModel.cpp
  GameList/GameListModel.h
  GameList/GameTracker.cpp
  GameList/GameTracker.h
  GameList/GridProxyModel.cpp
  GameList/GridProxyModel.h
  GameList/ListProxyModel.cpp
  GameList/ListProxyModel.h
  GCMemcardCreateNewDialog.cpp
  GCMemcardCreateNewDialog.h
  GCMemcardManager.cpp
  GCMemcardManager.h
  QtUtils/BlockUserInputFilter.cpp
  QtUtils/BlockUserInputFilter.h
  NetPlay/ChunkedProgressDialog.cpp
  NetPlay/ChunkedProgressDialog.h
  NetPlay/GameListDialog.cpp
  NetPlay/GameListDialog.h
  NetPlay/MD5Dialog.cpp
  NetPlay/MD5Dialog.h
  NetPlay/NetPlayBrowser.cpp
  NetPlay/NetPlayBrowser.h
  NetPlay/NetPlayDialog.cpp
  NetPlay/NetPlayDialog.h
  NetPlay/NetPlaySetupDialog.cpp
  NetPlay/NetPlaySetupDialog.h
  NetPlay/PadMappingDialog.cpp
  NetPlay/PadMappingDialog.h
  QtUtils/DolphinFileDialog.cpp
  QtUtils/DolphinFileDialog.h
  QtUtils/DoubleClickEventFilter.cpp
  QtUtils/DoubleClickEventFilter.h
  QtUtils/ElidedButton.cpp
  QtUtils/ElidedButton.h
  QtUtils/FileOpenEventFilter.cpp
  QtUtils/FileOpenEventFilter.h
  QtUtils/FlowLayout.cpp
  QtUtils/FlowLayout.h
  QtUtils/ModalMessageBox.cpp
  QtUtils/ModalMessageBox.h
  QtUtils/ParallelProgressDialog.h
  QtUtils/PartiallyClosableTabWidget.cpp
  QtUtils/PartiallyClosableTabWidget.h
  QtUtils/ImageConverter.cpp
  QtUtils/ImageConverter.h
  QtUtils/SignalBlocking.h
  QtUtils/UTF8CodePointCountValidator.cpp
  QtUtils/UTF8CodePointCountValidator.h
  QtUtils/WindowActivationEventFilter.cpp
  QtUtils/WindowActivationEventFilter.h
  QtUtils/WinIconHelper.cpp
  QtUtils/WinIconHelper.h
  QtUtils/WrapInScrollArea.cpp
  QtUtils/WrapInScrollArea.h
  QtUtils/AspectRatioWidget.cpp
  QtUtils/AspectRatioWidget.h
  QtUtils/NonDefaultQPushButton.cpp
  QtUtils/NonDefaultQPushButton.h
  ResourcePackManager.cpp
  ResourcePackManager.h
  RiivolutionBootWidget.cpp
  RiivolutionBootWidget.h
  Settings/AdvancedPane.cpp
  Settings/AdvancedPane.h
  Settings/AudioPane.cpp
  Settings/AudioPane.h
  Settings/BroadbandAdapterSettingsDialog.cpp
  Settings/BroadbandAdapterSettingsDialog.h
  Settings/GameCubePane.cpp
  Settings/GameCubePane.h
  Settings/GeneralPane.cpp
  Settings/GeneralPane.h
  Settings/InterfacePane.cpp
  Settings/InterfacePane.h
  Settings/PathPane.cpp
  Settings/PathPane.h
  Settings/WiiPane.cpp
  Settings/WiiPane.h
  Settings/USBDeviceAddToWhitelistDialog.cpp
  Settings/USBDeviceAddToWhitelistDialog.h
  TAS/GCTASInputWindow.cpp
  TAS/GCTASInputWindow.h
  TAS/WiiTASInputWindow.cpp
  TAS/WiiTASInputWindow.h
  TAS/TASCheckBox.cpp
  TAS/TASCheckBox.h
  TAS/TASInputWindow.cpp
  TAS/TASInputWindow.h
  TAS/TASSlider.cpp
  TAS/TASSlider.h
  TAS/StickWidget.cpp
  TAS/StickWidget.h
  TAS/IRWidget.cpp
  TAS/IRWidget.h
  Updater.cpp
  Updater.h
)

if (NOT WIN32)
  target_sources(dolphin-emu PRIVATE
    QtUtils/SignalDaemon.cpp
    QtUtils/SignalDaemon.h
  )
endif()

target_compile_definitions(dolphin-emu
PRIVATE
  -DQT_USE_QSTRINGBUILDER
  -DQT_NO_CAST_FROM_ASCII
  -DQT_NO_CAST_TO_ASCII
)

target_include_directories(dolphin-emu
PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${Qt${QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS}
)

target_link_libraries(dolphin-emu
PRIVATE
  core
  Qt${QT_VERSION_MAJOR}::Widgets
  uicommon
  imgui
)

if (WIN32)
  target_link_libraries(dolphin-emu
  PRIVATE
    gdi32.lib
    shell32.lib
  )
endif()

if (MSVC)
  set(qtGui "")
  set(qtGuiPriv "")
  set(qtWidgetsPriv "")
  list(TRANSFORM Qt6Gui_INCLUDE_DIRS PREPEND "/external:I" OUTPUT_VARIABLE qtGui)
  list(TRANSFORM Qt6Gui_PRIVATE_INCLUDE_DIRS PREPEND "/external:I" OUTPUT_VARIABLE qtGuiPriv)
  list(TRANSFORM Qt6Widgets_PRIVATE_INCLUDE_DIRS PREPEND "/external:I" OUTPUT_VARIABLE qtWidgetsPriv)
  target_compile_options(dolphin-emu PRIVATE "${qtGui}")
  target_compile_options(dolphin-emu PRIVATE "${qtGuiPriv}")
  target_compile_options(dolphin-emu PRIVATE "${qtWidgets}")

  if ("${QT_VERSION_MAJOR}" GREATER_EQUAL 6)
    # Qt6 requires RTTI
    remove_cxx_flag_from_target(dolphin-emu "/GR-")
    target_compile_options(dolphin-emu PRIVATE "/GR")
  else()
    # Add precompiled header
    target_link_libraries(audiocommon PRIVATE use_pch)
  endif()
endif()

if(WIN32)
  target_sources(dolphin-emu PRIVATE DolphinQt.manifest DolphinQt.rc)

  set_target_properties(dolphin-emu PROPERTIES
    DEBUG_POSTFIX    D
    OUTPUT_NAME      Dolphin
    WIN32_EXECUTABLE TRUE
  )

  # Copy Sys dir
  add_custom_command(TARGET dolphin-emu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Data/Sys" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Sys"
  )

  # Copy COPYING
  add_custom_command(TARGET dolphin-emu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/COPYING" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/COPYING"
  )

  # Copy Licenses dir
  add_custom_command(TARGET dolphin-emu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/LICENSES" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Licenses"
  )

  # Copy qt.conf
  add_custom_command(TARGET dolphin-emu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/qt.conf.win" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qt.conf"
  )

  # Delegate to Qt's official deployment binary on Windows to copy over the necessary Qt-specific libraries, etc.
  get_target_property(MOC_EXECUTABLE_LOCATION Qt${QT_VERSION_MAJOR}::moc IMPORTED_LOCATION)
  get_filename_component(QT_BINARY_DIRECTORY "${MOC_EXECUTABLE_LOCATION}" DIRECTORY)
  find_program(WINDEPLOYQT_EXE windeployqt HINTS "${QT_BINARY_DIRECTORY}")

  if ("${QT_VERSION_MAJOR}" LESS 6)
    set(NO_ANGLE_PARAM "--no-angle")
  else()
    # parameter no longer exists in Qt6
    set(NO_ANGLE_PARAM "")
  endif()

  # Note: We set the PATH for the duration of this command so that the
  #       deployment application is able to locate the Qt libraries to copy.
  #       if the necessary paths aren't already set beforehand.
  #
  #       For example, consider a hypothetical emulation project named Orca.
  #       Orca supplies its own version of Qt instead of having developers actually
  #       install the officially supported Qt libraries -- a method that would make
  #       wrangling around with Qt through CMake much nicer and lessen the external
  #       library maintenance burden of the project, but alas.
  #
  #       In this case, as Qt is not installed through the official binary, this also
  #       means proper path variables will not be set up, thus the need to ensure they're
  #       always set up.
  #
  add_custom_command(TARGET dolphin-emu POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E env PATH="${QT_BINARY_DIRECTORY}"
            "${WINDEPLOYQT_EXE}" --libdir="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
                                 --plugindir="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/QtPlugins"
                                 $<IF:$<CONFIG:Debug>,--debug,--release>
                                 --no-translations
                                 --no-compiler-runtime
                                 --no-system-d3d-compiler
                                 "${NO_ANGLE_PARAM}"
                                 --no-opengl-sw
                                 "$<TARGET_FILE:dolphin-emu>"
  )
endif()

# Handle localization
find_package(Gettext)

if(WIN32 AND NOT Gettext_FOUND)
  message(STATUS "Using Gettext from Externals")
  set(GETTEXT_MSGFMT_EXECUTABLE "${CMAKE_SOURCE_DIR}/Externals/gettext/msgfmt.exe")
endif()

if(GETTEXT_MSGFMT_EXECUTABLE)
  set(pot_file "${CMAKE_SOURCE_DIR}/Languages/po/dolphin-emu.pot")
  file(GLOB LINGUAS ${CMAKE_SOURCE_DIR}/Languages/po/*.po)

  target_sources(dolphin-emu PRIVATE ${pot_file} ${LINGUAS})
  source_group("Localization" FILES ${LINGUAS})
  source_group("Localization\\\\Generated" FILES ${pot_file})

  foreach(po ${LINGUAS})
    get_filename_component(lang ${po} NAME_WE)
    if(WIN32)
      set(mo_dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Languages)
      set(mo ${mo_dir}/${lang}.mo)
    else()
      set(mo_dir ${CMAKE_CURRENT_BINARY_DIR}/${lang})
      set(mo ${mo_dir}/dolphin-emu.mo)
    endif()

    target_sources(dolphin-emu PRIVATE ${mo})
    source_group("Localization\\\\Generated" FILES ${mo})

    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
      set_source_files_properties(${mo} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/${lang}.lproj")
    else()
      install(FILES ${mo} DESTINATION share/locale/${lang}/LC_MESSAGES)
    endif()

    if(WIN32)
      add_custom_command(OUTPUT ${mo}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${mo_dir}
        COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${mo} ${po}
        DEPENDS ${po}
      )
    else()
      add_custom_command(OUTPUT ${mo}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${mo_dir}
        COMMAND ${GETTEXT_MSGMERGE_EXECUTABLE} --quiet --update --backup=none -s ${po} ${pot_file}
        COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${mo} ${po}
        DEPENDS ${po}
      )
    endif()
  endforeach()
endif()

if(APPLE)
  include(BundleUtilities)
  set(BUNDLE_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Dolphin.app)

  # Ask for an application bundle.
  set_target_properties(dolphin-emu PROPERTIES
    MACOSX_BUNDLE true
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in
    XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS "${CMAKE_CURRENT_SOURCE_DIR}/DolphinEmu.entitlements"
    XCODE_ATTRIBUTE_OTHER_CODE_SIGN_FLAGS "--deep --options=runtime"
    OUTPUT_NAME Dolphin
    )

  # Copy qt.conf into the bundle
  target_sources(dolphin-emu PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/qt.conf")
  set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/qt.conf" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

  # Copy icon into the bundle
  target_sources(dolphin-emu PRIVATE "${CMAKE_SOURCE_DIR}/Data/Dolphin.icns")
  set_source_files_properties("${CMAKE_SOURCE_DIR}/Data/Dolphin.icns" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

  # Plugins have to be manually included with Qt 6
  if (QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6QMacStylePlugin REQUIRED PATHS ${Qt6Widgets_DIR})
    find_package(Qt6QCocoaIntegrationPlugin REQUIRED PATHS ${Qt6Gui_DIR})
  endif()

  # Copy Qt plugins into the bundle
  get_target_property(qtcocoa_location Qt${QT_VERSION_MAJOR}::QCocoaIntegrationPlugin LOCATION)
  target_sources(dolphin-emu PRIVATE "${qtcocoa_location}")
  set_source_files_properties("${qtcocoa_location}" PROPERTIES MACOSX_PACKAGE_LOCATION MacOS/platforms)

  get_target_property(qtmacstyle_location Qt${QT_VERSION_MAJOR}::QMacStylePlugin LOCATION)
  target_sources(dolphin-emu PRIVATE "${qtmacstyle_location}")
  set_source_files_properties("${qtmacstyle_location}" PROPERTIES MACOSX_PACKAGE_LOCATION MacOS/styles)

  # Copy resources into the bundle
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Data/Sys")
  file(GLOB_RECURSE resources RELATIVE "${CMAKE_SOURCE_DIR}/Data" "${CMAKE_SOURCE_DIR}/Data/Sys/*")
  foreach(res ${resources})
    target_sources(dolphin-emu PRIVATE "${CMAKE_SOURCE_DIR}/Data/${res}")
    get_filename_component(resdir "${res}" DIRECTORY)
    set_source_files_properties("${CMAKE_SOURCE_DIR}/Data/${res}" PROPERTIES
      MACOSX_PACKAGE_LOCATION "Resources/${resdir}")
    source_group("Resources" FILES "${CMAKE_SOURCE_DIR}/Data/${res}")
  endforeach()

  # Copy MoltenVK into the bundle
  if(ENABLE_VULKAN)
    if(USE_BUNDLED_MOLTENVK)
      add_dependencies(dolphin-emu MoltenVK)
      ExternalProject_Get_Property(MoltenVK SOURCE_DIR)
      target_sources(dolphin-emu PRIVATE "${SOURCE_DIR}/Package/Release/MoltenVK/dylib/macOS/libMoltenVK.dylib")
      set_source_files_properties("${SOURCE_DIR}/Package/Release/MoltenVK/dylib/macOS/libMoltenVK.dylib" PROPERTIES MACOSX_PACKAGE_LOCATION Frameworks GENERATED ON)
    else()
      find_file(MOLTENVK_DYLIB NAMES libMoltenVK.dylib PATH_SUFFIXES lib)
      if(NOT MOLTENVK_DYLIB)
        message(FATAL_ERROR "Couldn't find libMoltenVK.dylib.  Enable USE_BUNDLED_MOLTENVK?")
      endif()
      target_sources(dolphin-emu PRIVATE ${MOLTENVK_DYLIB})
      set_source_files_properties(${MOLTENVK_DYLIB} PROPERTIES MACOSX_PACKAGE_LOCATION Frameworks)
    endif()
  endif()

  if(NOT APPLE)
    # Update library references to make the bundle portable
    include(DolphinPostprocessBundle)
    dolphin_postprocess_bundle(dolphin-emu)
  endif()
  # Fix rpath
  add_custom_command(TARGET dolphin-emu
    POST_BUILD COMMAND
    ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@executable_path/../Frameworks/"
    $<TARGET_FILE:dolphin-emu>)

  if(MACOS_CODE_SIGNING)
    # Code sign make file builds
    add_custom_command(TARGET dolphin-emu
      POST_BUILD COMMAND
      /usr/bin/codesign -f -s "${MACOS_CODE_SIGNING_IDENTITY}" --deep --options=runtime --entitlements "${CMAKE_SOURCE_DIR}/Source/Core/DolphinQt/DolphinEmu$<$<CONFIG:Debug>:Debug>.entitlements" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Dolphin.app" || true)

    # Code sign builds for build systems that do have release/debug variants (Xcode)
    add_custom_command(TARGET dolphin-emu
      POST_BUILD COMMAND
      /usr/bin/codesign -f -s "${MACOS_CODE_SIGNING_IDENTITY}" --deep --options=runtime --entitlements "${CMAKE_SOURCE_DIR}/Source/Core/DolphinQt/DolphinEmuDebug.entitlements" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/Dolphin.app" || true)

    add_custom_command(TARGET dolphin-emu
      POST_BUILD COMMAND
      /usr/bin/codesign -f -s "${MACOS_CODE_SIGNING_IDENTITY}" --deep --options=runtime --entitlements "${CMAKE_SOURCE_DIR}/Source/Core/DolphinQt/DolphinEmu.entitlements" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/Dolphin.app" || true)
  endif()
else()
  install(TARGETS dolphin-emu RUNTIME DESTINATION ${bindir})
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND STEAM)
  # Set that we want ORIGIN in FLAGS.
  # We also want RPATH, not RUNPATH, so disable the new tags.
  target_link_options(dolphin-emu
  PRIVATE
    LINKER:-z,origin
    LINKER:--disable-new-dtags
  )

  # For Steam Runtime builds, our Qt shared libraries will be in a "lib" folder.
  set_target_properties(dolphin-emu PROPERTIES
    BUILD_WITH_INSTALL_RPATH true
    INSTALL_RPATH "\$ORIGIN/lib"
  )

  add_custom_command(TARGET dolphin-emu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib"
    COMMAND cp -P "${QT_DIR}/../../*.so*" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${QT_DIR}/../../../plugins/platforms" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/platforms"
  )

  # Copy qt.conf
  target_sources(dolphin-emu PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/qt.conf")
  add_custom_command(TARGET dolphin-emu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/qt.conf" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qt.conf"
  )

  # Mark all data files as resources
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Data/Sys")
  file(GLOB_RECURSE resources RELATIVE "${CMAKE_SOURCE_DIR}/Data" "${CMAKE_SOURCE_DIR}/Data/Sys/*")
  foreach(res ${resources})
    target_sources(dolphin-emu PRIVATE "${CMAKE_SOURCE_DIR}/Data/${res}")
    source_group("Resources" FILES "${CMAKE_SOURCE_DIR}/Data/${res}")
  endforeach()

  # Copy Sys folder
  add_custom_command(TARGET dolphin-emu POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Data/Sys" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Sys"
  )
endif()

if(USE_MGBA)
  target_sources(dolphin-emu PRIVATE
    GBAHost.cpp
    GBAHost.h
    GBAWidget.cpp
    GBAWidget.h
  )
endif()

if(USE_DISCORD_PRESENCE)
  target_compile_definitions(dolphin-emu PRIVATE -DUSE_DISCORD_PRESENCE)
endif()
