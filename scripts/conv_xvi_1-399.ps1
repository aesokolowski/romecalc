if (-not (Test-Path -Path .\co1-399.txt)) {
  New-Item -Path .\co1-399.txt | Out-Null 
}

$fn1 = ".\co1-399.txt"
Set-Content -Path $fn1 -Value "Testing the converters for 1 - 399:"
for ($i = 1; $i -lt 400; $i++) {
    $rn = (.\rocal $i);
    Add-Content -Path $fn1 -Value $rn
    Add-Content -Path $fn1 -Value (.\testconvs $rn);
}
