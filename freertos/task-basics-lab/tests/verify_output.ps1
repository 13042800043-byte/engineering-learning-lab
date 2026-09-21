param(
    [Parameter(Mandatory = $true)]
    [string]$Executable
)

$ErrorActionPreference = 'Stop'

if (-not (Test-Path -LiteralPath $Executable -PathType Leaf)) {
    throw "FreeRTOS lab executable not found: $Executable"
}

$processInfo = [System.Diagnostics.ProcessStartInfo]::new()
$processInfo.FileName = (Resolve-Path -LiteralPath $Executable).Path
$processInfo.UseShellExecute = $false
$processInfo.RedirectStandardOutput = $true
$processInfo.RedirectStandardError = $true
$processInfo.CreateNoWindow = $true

$process = [System.Diagnostics.Process]::new()
$process.StartInfo = $processInfo

if (-not $process.Start()) {
    throw 'Unable to start the FreeRTOS lab executable.'
}

if (-not $process.WaitForExit(15000)) {
    $process.Kill($true)
    throw 'FreeRTOS lab timed out after 15 seconds.'
}

$standardOutput = $process.StandardOutput.ReadToEnd()
$standardError = $process.StandardError.ReadToEnd()

Write-Output $standardOutput

if ($standardError) {
    Write-Output 'STDERR:'
    Write-Output $standardError
}

if ($process.ExitCode -ne 0) {
    throw "FreeRTOS lab exited with code $($process.ExitCode)."
}

$requiredOutput = @(
    'LAB START',
    '[HIGH] run 1',
    '[LOW] run 1',
    'LAB PASS: both tasks reached their target counts'
)

foreach ($expectedText in $requiredOutput) {
    if (-not $standardOutput.Contains($expectedText)) {
        throw "Expected output was not found: $expectedText"
    }
}
