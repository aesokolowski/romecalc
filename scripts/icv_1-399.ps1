if (-not (Test-Path -Path ${pwd}\to1-399.txt)) {
    New-Item -Path "${pwd}\to1-399.txt" | Out-Null
}

Set-Content -Path ${pwd}\to1-399.txt -Value "Testing icv_check for 1 - 399"

