## Run on the terminal
```shell
g++ ./route.cpp -o ./route.exe
$files = @('bench1.txt', 'bench2.txt', 'bench3.txt', 'bench4.txt', 'bench5.txt', 'bench6.txt')
foreach ($file in $files) {
    Write-Host "Reading $file..."
    ./route.exe $file
}
```
## Acknowledgements
This project uses code from [channel-router](https://github.com/rgongw0414/channel-router/tree/main) by GONG-CHI WANG(rgongw0414), which is licensed under the MIT License.
