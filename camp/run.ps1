# Usage:
#   .\run.ps1            everything
#   .\run.ps1 ll         linked list only   (also: st, qu)
#   .\run.ps1 LL-6       a single problem
#   .\run.ps1 mock       Monday's mock exam set (LL-6, LL-9, ST-5, ST-9, QU-8, QU-9)
param([string]$Filter = "")

$root = $PSScriptRoot
New-Item -ItemType Directory -Force "$root/build" | Out-Null
$exe = "$root/build/camp.exe"

g++ -std=c++17 -Wall -g -O0 "$root/tests/main.cpp" -o $exe
if ($LASTEXITCODE -ne 0) {
    Write-Host "`nCompile error (see above). Check the file name and line number." -ForegroundColor Red
    exit 1
}
& $exe $Filter
