@echo off
:: Read config file config_win.txt
for /F "eol=# delims== tokens=1,*" %%a in (config_win.txt) do (
    if NOT "%%a"=="" if NOT "%%b"=="" (set %%a=%%b)
)
echo QT_BASE: %QT_BASE%
echo BUILD_DIR: %BUILD_DIR%
echo VS_VERSION: %VS_VERSION%
:: Generate
cmake --version
cmake -G %VS_VERSION% -DQT_BASE=%QT_BASE% -S src -B %BUILD_DIR%
:: Build
cmake --build %BUILD_DIR%
:: Run
set PATH=%PATH%;%QT_BASE:"=%/bin
echo running "%BUILD_DIR:"=%/Debug/Lachs.exe"
"%BUILD_DIR:"=%/Debug/Lachs.exe"