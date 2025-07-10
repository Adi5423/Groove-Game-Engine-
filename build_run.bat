@echo off
setlocal

REM --- SETTINGS ---
set BUILD_ROOT=build
set BUILD_SUBDIR=build-x64/windows-debug
set BUILD_DIR=%BUILD_ROOT%\%BUILD_SUBDIR%
set EXE_DIR=%BUILD_DIR%\sandbox
set EXE_PATH=%EXE_DIR%\Sandbox.exe

REM --- Step 0: Clean old build folder ---
echo.
echo Cleaning previous build (if any)...
rmdir /s /q "%BUILD_ROOT%" 2>nul

REM --- Step 1: Go to script folder ---
cd /d "%~dp0"

REM --- Step 2: Configure ---
echo.
echo Configuring with CMake...
cmake -S . -B "%BUILD_DIR%" ^
  -DCMAKE_BUILD_TYPE=Debug ^
  -DCMAKE_EXPORT_COMPILE_COMMANDS=YES ^
  -DCMAKE_INSTALL_PREFIX="%BUILD_DIR%\install" ^
  -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake ^
  -DVCPKG_TARGET_TRIPLET=x64-windows

if ERRORLEVEL 1 (
  echo ❌ Configuration failed!
  pause
  exit /b 1
)

REM --- Step 3: Build ---
echo.
echo Building the project...
cmake --build "%BUILD_DIR%"
if ERRORLEVEL 1 (
  echo ❌ Build failed!
  pause
  exit /b 1
)

REM --- Step 4: Create log folder ---


REM --- Step 5: Run the exe from its folder (so logs go there) ---
echo.
echo Launching Sandbox.exe...
if not exist "%EXE_PATH%" (
  echo ❌ Executable not found: %EXE_PATH%
  pause
  exit /b 1
)

pushd "%EXE_DIR%"
Sandbox.exe
popd

REM 6) Move logs to logs folder if they exist

if exist "sandbox\imgui.ini" move /Y "sandbox\imgui.ini" "logs\imgui.ini" >nul
if exist "sandbox\Groove.log" move /Y "sandbox\Groove.log" "logs\Groove.log" >nul

REM --- Step 7: Done ---
echo.
echo Press any key to close...
pause