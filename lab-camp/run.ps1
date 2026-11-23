# Usage (from the lab-camp folder or with the full path):
#   .\run.ps1                 list the labs
#   .\run.ps1 L01             compile your lab01.cpp with the tests and run them   (also: 1, l1, 01)
#   .\run.ps1 L01 L01-B       run a single question
#   .\run.ps1 L01 -Solution   run the same tests against the reference solution
param([string]$Lab = "", [string]$Only = "", [switch]$Solution)

$root = $PSScriptRoot
$labs = Get-ChildItem "$root/week*/*" -Directory | Where-Object { $_.Name -match "^[LCP]\d\d-" } | Sort-Object Name

if (-not $Lab) {
    Write-Host "`nLabs:"
    foreach ($d in $labs) { Write-Host ("  {0,-4} {1}" -f $d.Name.Substring(0, 3), $d.Parent.Name + "/" + $d.Name) }
    Write-Host "`nExample: .\run.ps1 L01`n"
    exit 0
}

$prefix = if ($Lab -match '^[cCpP]') { $Lab.Substring(0, 1).ToUpper() } else { "L" }
$num = [int]($Lab -replace '[^0-9]', '')
$id = "$prefix{0:D2}" -f $num
$dir = $labs | Where-Object { $_.Name.StartsWith("$id-") } | Select-Object -First 1
if (-not $dir) { Write-Host "No lab named $id. Run .\run.ps1 to see the list." -ForegroundColor Red; exit 1 }

$sources = @()
foreach ($f in Get-ChildItem $dir.FullName -Filter *.cpp | Where-Object { $_.Name -notlike "warmup*" -and $_.Name -notlike "main*" }) {
    $sol = Join-Path "$root/solutions/$id" $f.Name
    if ($Solution -and (Test-Path $sol)) { $sources += $sol } else { $sources += $f.FullName }
}
$sources += (Get-ChildItem "$($dir.FullName)/tests" -Filter *.cpp).FullName
$sources += "$root/framework/main.cpp"

New-Item -ItemType Directory -Force "$root/build" | Out-Null
$exe = "$root/build/$id" + $(if ($Solution) { "-solution" } else { "" }) + ".exe"

$solInc = if ($Solution) { @("-I$root/solutions/$id") } else { @() }
g++ -std=c++17 -Wall -Wextra -Wno-unused-parameter -g -O0 @solInc "-I$($dir.FullName)" "-I$root/framework" @sources -o $exe
if ($LASTEXITCODE -ne 0) {
    Write-Host "`nCompile error (see above). Read the first error: file name, line number, message." -ForegroundColor Red
    exit 1
}
& $exe $Only
exit $LASTEXITCODE
