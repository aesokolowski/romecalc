$fn1 = ".\ran1-399.txt"

if (-not (Test-Path -Path $fn1)) {
  New-Item -Path $fn1 | Out-Null
}

Set-Content -Path $fn1 -Value "Testing 399 random strings of Roman Numeral characters I/i thru C/c:"
for ($i = 0; $i -lt 399; $i++) {
  $numchars = (Get-Random -Maximum 10) + 1
  $str = ""
  for ($j = 0; $j -lt $numchars; $j++) {
    $str += "I", "i", "V", "v", "X", "x", "L", "l", "C", "c" | Get-Random
  } 
  Add-Content -Path $fn1 -Value $str
  Add-Content -Path $fn1 -Value (.\rocal $str)
}
