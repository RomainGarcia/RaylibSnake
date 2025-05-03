$outDir = "wasm-dist"

# Create output directory if it doesn't exist
if (!(Test-Path $outDir)) {
    New-Item -ItemType Directory -Path $outDir | Out-Null
}

# Get files to compile
$cppFiles = Get-ChildItem -Recurse -Filter *.cpp -Path src | ForEach-Object { $_.FullName }

# Include directories with headers
$includeDirs = Get-ChildItem -Recurse -Filter *.h -Path src |
    ForEach-Object { $_.Directory.FullName } |
    Sort-Object -Unique

# Add additional include directories
$includeDirs += (Resolve-Path "cmake-build-release/_deps/raylib-src/src").Path
$includeDirs += (Resolve-Path "src").Path

# Build include flags
$includeFlags = $includeDirs | ForEach-Object { "-I" + "`"" + $_ + "`"" }

# Copy assets folder into output directory
$assetsSrc = "assets"
$assetsDest = "$outDir/assets"

# Compile
em++ $cppFiles `
    -o "$outDir/index.html" `
    $includeFlags `
    "D:/Dev/Cpp/Libs/raylib/src/libraylib.a" `
    -s USE_GLFW=3 `
    -s ASYNCIFY `
    -s WASM=1 `
    -s ALLOW_MEMORY_GROWTH=1 `
    -s STACK_SIZE=2097152 `
    -s ASSERTIONS=2 `
    --preload-file assets@assets `
    -s EXPORTED_RUNTIME_METHODS='["HEAPF32"]' `
    -std=c++20
