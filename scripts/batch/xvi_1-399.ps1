$fn1 = ".\to1-399.txt"

if (-not (Test-Path -Path $fn1)) {
  New-Item -Path $fn1 | Out-Null
}

Set-Content -Path $fn1 -Value "Testing check_xvi for 1 - 399:"
for ($i = 1; $i -lt 400; $i++) {
  $rn = (.\rocal $i)
  Add-Content -Path $fn1 -Value $rn
  Add-Content -Path $fn1 -Value (.\testutils $rn)
}
