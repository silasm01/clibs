# Hardcoded directories
$startDir = "C:\Users\silas\code\clibs"
$linkDirH = "C:\cygwin64\usr\include"
$linkDirA = "C:\cygwin64\lib"

# Check if the start directory exists
if (-Not (Test-Path $startDir)) {
    Write-Host "Error: Start directory '$startDir' does not exist."
    exit 1
}

# Create the symlink directories if they do not exist
if (-Not (Test-Path $linkDirH)) {
    New-Item -ItemType Directory -Path $linkDirH
}
if (-Not (Test-Path $linkDirA)) {
    New-Item -ItemType Directory -Path $linkDirA
}

# Get all .h files recursively
$filesH = Get-ChildItem -Path $startDir -Recurse -Include *.h

# Loop through each .h file and create a symlink
foreach ($file in $filesH) {
    # Create the target path for the symlink in the .h symlink directory
    $targetPathH = Join-Path -Path $linkDirH -ChildPath $file.Name

    # Remove the symlink if it already exists
    if (Test-Path $targetPathH) {
        Remove-Item $targetPathH
    }

    # Create the symlink if it doesn't already exist
    if (-Not (Test-Path $targetPathH)) {
        New-Item -ItemType SymbolicLink -Path $targetPathH -Target $file.FullName
        Write-Host "Created symlink for .h: $targetPathH -> $($file.FullName)"
    } else {
        Write-Host "Symlink already exists for .h: $targetPathH"
    }
}

# Get all .a files recursively
$filesA = Get-ChildItem -Path $startDir -Recurse -Include *.a

# Loop through each .a file and create a symlink
foreach ($file in $filesA) {
    # Create the target path for the symlink in the .a symlink directory
    $targetPathA = Join-Path -Path $linkDirA -ChildPath $file.Name

    # Remove the symlink if it already exists
    if (Test-Path $targetPathA) {
        Remove-Item $targetPathA
    }

    # Create the symlink if it doesn't already exist
    if (-Not (Test-Path $targetPathA)) {
        New-Item -ItemType SymbolicLink -Path $targetPathA -Target $file.FullName
        Write-Host "Created symlink for .a: $targetPathA -> $($file.FullName)"
    } else {
        Write-Host "Symlink already exists for .a: $targetPathA"
    }
}

Write-Host "Symlinking complete."
