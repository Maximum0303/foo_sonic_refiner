param(
    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Release"
)

$ErrorActionPreference = "Stop"

$ProjectRoot = Split-Path -Parent $PSScriptRoot
$Project = Join-Path $ProjectRoot "foo_sonic_refiner.vcxproj"
$OutputDll = Join-Path $ProjectRoot "x64\$Configuration\foo_sonic_refiner.dll"
$DistRoot = Join-Path $ProjectRoot "dist"
$StageRoot = Join-Path $DistRoot "foo_sonic_refiner"
$PackagePath = Join-Path $DistRoot "foo_sonic_refiner_v0.6.1.fb2k-component"
$TempZip = Join-Path $DistRoot "foo_sonic_refiner_v0.6.1.zip"

$SdkRoot = [IO.Path]::GetFullPath((Join-Path $ProjectRoot "..\.."))
$DevRoot = [IO.Path]::GetFullPath((Join-Path $SdkRoot ".."))
$WtlInclude = Join-Path $DevRoot "WTL\Include"
$DirectoryTargets = Join-Path $SdkRoot "Directory.Build.targets"

$RequiredWtlFiles = @(
    "atlapp.h",
    "atlctrls.h",
    "atlgdi.h",
    "atlframe.h",
    "atlwinx.h"
)

if (-not (Test-Path $WtlInclude -PathType Container)) {
    throw @"
WTL Include folder was not found.

Expected:
  $WtlInclude

Extract WTL so that this file exists:
  $WtlInclude\atlapp.h
"@
}

foreach ($FileName in $RequiredWtlFiles) {
    $FullPath = Join-Path $WtlInclude $FileName
    if (-not (Test-Path $FullPath -PathType Leaf)) {
        throw "WTL is incomplete. Missing file: $FullPath"
    }
}

$VsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $VsWhere)) {
    throw "vswhere.exe was not found. Check Visual Studio 2022 installation."
}

$MsBuild = & $VsWhere -latest -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe |
    Select-Object -First 1

if (-not $MsBuild -or -not (Test-Path $MsBuild)) {
    throw "MSBuild.exe was not found."
}

# All SDK dependency projects must use the same WTL folder.
# Directory.Build.targets is temporarily injected at the SDK root so it also
# applies to pfc, libPPUI, SDK helpers and the component client.
$HadOriginalTargets = Test-Path $DirectoryTargets
$OriginalTargetsBytes = $null

if ($HadOriginalTargets) {
    $OriginalTargetsBytes = [IO.File]::ReadAllBytes($DirectoryTargets)
    $OriginalTargetsText = [Text.Encoding]::UTF8.GetString($OriginalTargetsBytes)

    if ($OriginalTargetsText -notmatch "</Project>") {
        throw "Existing Directory.Build.targets could not be safely extended: $DirectoryTargets"
    }

    $Injection = @"
  <ItemDefinitionGroup>
    <ClCompile>
      <AdditionalIncludeDirectories>$WtlInclude;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
    </ClCompile>
  </ItemDefinitionGroup>
"@

    $TemporaryTargetsText = $OriginalTargetsText -replace "</Project>", "$Injection</Project>"
}
else {
    $TemporaryTargetsText = @"
<Project xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemDefinitionGroup>
    <ClCompile>
      <AdditionalIncludeDirectories>$WtlInclude;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
    </ClCompile>
  </ItemDefinitionGroup>
</Project>
"@
}

try {
    [IO.File]::WriteAllText(
        $DirectoryTargets,
        $TemporaryTargetsText,
        [Text.UTF8Encoding]::new($false)
    )

    Write-Host "WTL Include:"
    Write-Host "  $WtlInclude"
    Write-Host ""
    Write-Host "Building Sonic Refiner: $Configuration / x64"

    & $MsBuild $Project /t:Rebuild /m /v:minimal /p:Configuration=$Configuration /p:Platform=x64

    if ($LASTEXITCODE -ne 0) {
        throw "Build failed."
    }
}
finally {
    if ($HadOriginalTargets) {
        [IO.File]::WriteAllBytes($DirectoryTargets, $OriginalTargetsBytes)
    }
    else {
        Remove-Item $DirectoryTargets -Force -ErrorAction SilentlyContinue
    }
}

if (-not (Test-Path $OutputDll)) {
    throw "Built DLL was not found: $OutputDll"
}

Remove-Item $StageRoot -Recurse -Force -ErrorAction SilentlyContinue
New-Item $StageRoot -ItemType Directory -Force | Out-Null
New-Item $DistRoot -ItemType Directory -Force | Out-Null

Copy-Item $OutputDll (Join-Path $StageRoot "foo_sonic_refiner.dll")

function Write-WindowsTextFile {
    param(
        [Parameter(Mandatory = $true)]
        [string]$SourcePath,

        [Parameter(Mandatory = $true)]
        [string]$DestinationPath
    )

    $Text = [IO.File]::ReadAllText(
        $SourcePath,
        [Text.Encoding]::UTF8
    )

    # Normalize any CRLF, CR or LF source to Windows CRLF.
    $Text = $Text.Replace("`r`n", "`n")
    $Text = $Text.Replace("`r", "`n")
    $Text = $Text.Replace("`n", "`r`n")

    [IO.File]::WriteAllText(
        $DestinationPath,
        $Text,
        [Text.UTF8Encoding]::new($false)
    )
}

Write-WindowsTextFile `
    (Join-Path $ProjectRoot "LICENSE.txt") `
    (Join-Path $StageRoot "MIT_LICENSE.txt")

Write-WindowsTextFile `
    (Join-Path $ProjectRoot "COMPONENT_README.txt") `
    (Join-Path $StageRoot "readme.txt")

Write-WindowsTextFile `
    (Join-Path $ProjectRoot "THIRD_PARTY_NOTICES.txt") `
    (Join-Path $StageRoot "third_party_notices.txt")

Remove-Item $PackagePath -Force -ErrorAction SilentlyContinue
Remove-Item $TempZip -Force -ErrorAction SilentlyContinue

Compress-Archive -Path (Join-Path $StageRoot "*") -DestinationPath $TempZip -CompressionLevel Optimal
Move-Item $TempZip $PackagePath

$Hash = Get-FileHash $PackagePath -Algorithm SHA256
$HashLine = "$($Hash.Hash.ToLower())  $([IO.Path]::GetFileName($PackagePath))"
Set-Content -Path (Join-Path $DistRoot "SHA256SUMS.txt") -Value $HashLine -Encoding ascii

Write-Host ""
Write-Host "Completed:"
Write-Host "  $PackagePath"
Write-Host "  $(Join-Path $DistRoot 'SHA256SUMS.txt')"
