# Run on the terminal
```shell
g++ ./route.cpp -o ./route.exe
$files = @('bench1.txt', 'bench2.txt', 'bench3.txt', 'bench4.txt', 'bench5.txt', 'bench6.txt')
foreach ($file in $files) {
    Write-Host "Reading $file..."
    ./route.exe $file
}
```
