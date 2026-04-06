Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

# ============================================================
# CONFIGURATION FIXE
# ============================================================

$QtVersion = "6.10.0"
$QtArch    = "win64_msvc2022_64"
$QtBaseDir = "C:\Qt"

$ConfigurePreset = "ninja-release"
$BuildPreset     = "build-ninja-release"

# ============================================================
# HELPERS
# ============================================================

function Step($msg) {
    Write-Host "`n=== $msg ===" -ForegroundColor Yellow
}

function Require-Command($name, $errorMsg) {
    if (-not (Get-Command $name -ErrorAction SilentlyContinue)) {
        throw $errorMsg
    }
}

function Refresh-Path {
    $machine = [System.Environment]::GetEnvironmentVariable("Path", "Machine")
    $user    = [System.Environment]::GetEnvironmentVariable("Path", "User")
    $env:Path = "$machine;$user"
}

# ============================================================
# HEADER
# ============================================================

Write-Host "Build configuration:" -ForegroundColor Cyan
Write-Host "  Qt version   : $QtVersion"
Write-Host "  Qt arch      : $QtArch"
Write-Host "  Generator    : Ninja"
Write-Host "  Preset       : $ConfigurePreset"

# ============================================================
# 1) PYTHON (REQUIS)
# ============================================================

Step "Checking Python"
Require-Command python "Python requis (3.10+). Installe Python avant de lancer ce script."
Require-Command pip    "pip introuvable (installation Python incorrecte)."

# ============================================================
# 2) AQTINSTALL
# ============================================================

Step "Checking aqtinstall"
if (-not (Get-Command aqt -ErrorAction SilentlyContinue)) {
    Step "Installing aqtinstall"
    python -m pip install --upgrade pip
    python -m pip install aqtinstall
}

# ============================================================
# 3) QT (VIA AQT)
# ============================================================

$QtRoot   = Join-Path $QtBaseDir "$QtVersion\msvc2022_64"
$QtCMake = Join-Path $QtRoot "bin\qt-cmake.bat"

if (-not (Test-Path $QtCMake)) {
    Step "Installing Qt $QtVersion ($QtArch)"
    aqt install-qt windows desktop $QtVersion $QtArch -m qtmultimedia -m qtbase -O $QtBaseDir
}

if (-not (Test-Path $QtCMake)) {
    throw "Qt installé mais qt-cmake introuvable ($QtCMake)"
}

# ============================================================
# 4) MSVC BUILD TOOLS 2022
# ============================================================

Step "Checking MSVC Build Tools 2022"

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $vswhere)) {
    Step "Installing Visual Studio 2022 Build Tools"
    winget install --id Microsoft.VisualStudio.2022.BuildTools --source winget `
        --override "--wait --quiet --add Microsoft.VisualStudio.Workload.VCTools"
}

if (-not (Test-Path $vswhere)) {
    throw "vswhere.exe introuvable ($vswhere)"
}

# ============================================================
# 5) INITIALISATION ENV MSVC (OBLIGATOIRE POUR NINJA)
# ============================================================

Step "Initializing MSVC environment"

$vsInstall = & $vswhere -latest -products * `
    -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
    -property installationPath

if (-not $vsInstall) {
    throw "Installation MSVC non détectée."
}

$vcvars = Join-Path $vsInstall "VC\Auxiliary\Build\vcvars64.bat"
if (-not (Test-Path $vcvars)) {
    throw "vcvars64.bat introuvable ($vcvars)"
}

cmd /c "`"$vcvars`" >nul && set" | ForEach-Object {
    $pair = $_.Split("=", 2)
    if ($pair.Length -eq 2) {
        Set-Item -Path "Env:$($pair[0])" -Value $pair[1]
    }
}

# ============================================================
# 6) NINJA
# ============================================================

Step "Checking Ninja"
if (-not (Get-Command ninja -ErrorAction SilentlyContinue)) {
    Step "Installing Ninja"
    winget install --id Ninja-build.Ninja --source winget
	
	# Recharge le PATH pour détecter ninja immédiatement
    Refresh-Path
}

# ============================================================
# 7) CMAKE
# ============================================================

Step "Checking CMake"
if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Step "Installing CMake"
    winget install --id Kitware.CMake --source winget
	
	Refresh-Path
}

# ============================================================
# 8) CONFIGURE + BUILD (PRESETS UNIQUEMENT)
# ============================================================

Step "Configure (qt-cmake --preset $ConfigurePreset)"

if (-not (Test-Path "CMakeLists.txt")) {
    throw "CMakeLists.txt introuvable (lance le script à la racine du projet)."
}
if (-not (Test-Path "CMakePresets.json")) {
    throw "CMakePresets.json introuvable."
}

& $QtCMake --preset $ConfigurePreset

Step "Build (cmake --build --preset $BuildPreset)"
cmake --build --preset $BuildPreset

# ============================================================
# 9) WINDEPLOYQT
# ============================================================

Step "Deploy Qt runtime (windeployqt)"

$WinDeployQt = Join-Path $QtRoot "bin\windeployqt.exe"
if (-not (Test-Path $WinDeployQt)) {
    throw "windeployqt.exe introuvable ($WinDeployQt)"
}

# Lit le nom du projet depuis CMakeLists.txt
$cmakeFile = "CMakeLists.txt"
if (Test-Path $cmakeFile) {
    $projectName = Select-String -Path $cmakeFile -Pattern 'project\((\w+)' | 
                   ForEach-Object { $_.Matches.Groups[1].Value }
    
    if ($projectName) {
        $ExePath = "build-ninja-release\$projectName.exe"
        if (Test-Path $ExePath) {
            Write-Host "Utilisation de : $ExePath"
        } else {
            Write-Warning "$ExePath non trouvé, recherche dynamique..."
            $ExePath = Get-ChildItem "build-ninja-release" -Filter "*.exe" | 
                       Select-Object -First 1 | 
                       ForEach-Object { $_.FullName }
        }
    }
}
if (-not (Test-Path $ExePath)) {
    throw "Executable introuvable ($ExePath)"
}

& $WinDeployQt `
    --release `
    --no-translations `
    --no-opengl-sw `
    --compiler-runtime `
    $ExePath

Write-Host "`nBUILD + DEPLOY SUCCESS" -ForegroundColor Green