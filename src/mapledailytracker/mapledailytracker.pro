QT       += core gui widgets

TARGET = mapledailytracker
TEMPLATE = app

RC_ICONS += MapleTracker.ico
ICON = MapleTracker.icns

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++20

SOURCES += \
        character.cpp \
        characterdialog.cpp \
        filemanager.cpp \
        main.cpp \
        mainwindow.cpp \
        mapleactiondialog.cpp \
        mapleactionlistwidgetitem.cpp \
        preferences.cpp \
        progress.cpp \
        progresscontent.cpp \
        qmodernprogressbar.cpp \
        resetchecker.cpp \
        trackertabcontent.cpp \
        trackertabwidget.cpp \
        trackerwidget.cpp

HEADERS += \
    characterdialog.h \
    mapleaction.h \
    character.h \
    filemanager.h \
    mapleactiondialog.h \
    mapleactionlistwidgetitem.h \
    preferences.h \
    progress.h \
    progresscontent.h \
    qmodernprogressbar.h \
    resetchecker.h \
    resetdata.h \
    savedata.h \
    mainwindow.h \
    trackertabcontent.h \
    trackertabwidget.h \
    trackerwidget.h \
    vendor/spdlog/async.h \
    vendor/spdlog/async_logger-inl.h \
    vendor/spdlog/async_logger.h \
    vendor/spdlog/cfg/argv.h \
    vendor/spdlog/cfg/env.h \
    vendor/spdlog/cfg/helpers-inl.h \
    vendor/spdlog/cfg/helpers.h \
    vendor/spdlog/common-inl.h \
    vendor/spdlog/common.h \
    vendor/spdlog/details/backtracer-inl.h \
    vendor/spdlog/details/backtracer.h \
    vendor/spdlog/details/circular_q.h \
    vendor/spdlog/details/console_globals.h \
    vendor/spdlog/details/file_helper-inl.h \
    vendor/spdlog/details/file_helper.h \
    vendor/spdlog/details/fmt_helper.h \
    vendor/spdlog/details/log_msg-inl.h \
    vendor/spdlog/details/log_msg.h \
    vendor/spdlog/details/log_msg_buffer-inl.h \
    vendor/spdlog/details/log_msg_buffer.h \
    vendor/spdlog/details/mpmc_blocking_q.h \
    vendor/spdlog/details/null_mutex.h \
    vendor/spdlog/details/os-inl.h \
    vendor/spdlog/details/os.h \
    vendor/spdlog/details/periodic_worker-inl.h \
    vendor/spdlog/details/periodic_worker.h \
    vendor/spdlog/details/registry-inl.h \
    vendor/spdlog/details/registry.h \
    vendor/spdlog/details/synchronous_factory.h \
    vendor/spdlog/details/tcp_client-windows.h \
    vendor/spdlog/details/tcp_client.h \
    vendor/spdlog/details/thread_pool-inl.h \
    vendor/spdlog/details/thread_pool.h \
    vendor/spdlog/details/udp_client-windows.h \
    vendor/spdlog/details/udp_client.h \
    vendor/spdlog/details/windows_include.h \
    vendor/spdlog/fmt/bin_to_hex.h \
    vendor/spdlog/fmt/bundled/args.h \
    vendor/spdlog/fmt/bundled/chrono.h \
    vendor/spdlog/fmt/bundled/color.h \
    vendor/spdlog/fmt/bundled/compile.h \
    vendor/spdlog/fmt/bundled/core.h \
    vendor/spdlog/fmt/bundled/format-inl.h \
    vendor/spdlog/fmt/bundled/format.h \
    vendor/spdlog/fmt/bundled/locale.h \
    vendor/spdlog/fmt/bundled/os.h \
    vendor/spdlog/fmt/bundled/ostream.h \
    vendor/spdlog/fmt/bundled/printf.h \
    vendor/spdlog/fmt/bundled/ranges.h \
    vendor/spdlog/fmt/bundled/xchar.h \
    vendor/spdlog/fmt/chrono.h \
    vendor/spdlog/fmt/compile.h \
    vendor/spdlog/fmt/fmt.h \
    vendor/spdlog/fmt/ostr.h \
    vendor/spdlog/fmt/ranges.h \
    vendor/spdlog/fmt/xchar.h \
    vendor/spdlog/formatter.h \
    vendor/spdlog/fwd.h \
    vendor/spdlog/logger-inl.h \
    vendor/spdlog/logger.h \
    vendor/spdlog/pattern_formatter-inl.h \
    vendor/spdlog/pattern_formatter.h \
    vendor/spdlog/sinks/android_sink.h \
    vendor/spdlog/sinks/ansicolor_sink-inl.h \
    vendor/spdlog/sinks/ansicolor_sink.h \
    vendor/spdlog/sinks/base_sink-inl.h \
    vendor/spdlog/sinks/base_sink.h \
    vendor/spdlog/sinks/basic_file_sink-inl.h \
    vendor/spdlog/sinks/basic_file_sink.h \
    vendor/spdlog/sinks/daily_file_sink.h \
    vendor/spdlog/sinks/dist_sink.h \
    vendor/spdlog/sinks/dup_filter_sink.h \
    vendor/spdlog/sinks/hourly_file_sink.h \
    vendor/spdlog/sinks/mongo_sink.h \
    vendor/spdlog/sinks/msvc_sink.h \
    vendor/spdlog/sinks/null_sink.h \
    vendor/spdlog/sinks/ostream_sink.h \
    vendor/spdlog/sinks/qt_sinks.h \
    vendor/spdlog/sinks/ringbuffer_sink.h \
    vendor/spdlog/sinks/rotating_file_sink-inl.h \
    vendor/spdlog/sinks/rotating_file_sink.h \
    vendor/spdlog/sinks/sink-inl.h \
    vendor/spdlog/sinks/sink.h \
    vendor/spdlog/sinks/stdout_color_sinks-inl.h \
    vendor/spdlog/sinks/stdout_color_sinks.h \
    vendor/spdlog/sinks/stdout_sinks-inl.h \
    vendor/spdlog/sinks/stdout_sinks.h \
    vendor/spdlog/sinks/syslog_sink.h \
    vendor/spdlog/sinks/systemd_sink.h \
    vendor/spdlog/sinks/tcp_sink.h \
    vendor/spdlog/sinks/udp_sink.h \
    vendor/spdlog/sinks/win_eventlog_sink.h \
    vendor/spdlog/sinks/wincolor_sink-inl.h \
    vendor/spdlog/sinks/wincolor_sink.h \
    vendor/spdlog/spdlog-inl.h \
    vendor/spdlog/spdlog.h \
    vendor/spdlog/stopwatch.h \
    vendor/spdlog/tweakme.h \
    vendor/spdlog/version.h


FORMS += \
        characterdialog.ui \
        mainwindow.ui \
        mapleactiondialog.ui \
        preferences.ui \
        progress.ui \
        progresscontent.ui \
        trackertabcontent.ui \
        trackertabwidget.ui \
        trackerwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    vendor/spdlog/fmt/bundled/fmt.license.rst

RESOURCES += \
    resources.qrc
