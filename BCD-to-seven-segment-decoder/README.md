
##  Berkeley SIS install
```shell
  sudo dpkg -i sis.deb
  sudo apt install -y make gcc bison flex build-essential
  export CFLAGS=-std=gnu90
```
## Additional libraries (if needed):
```shell
./configure prefix=/usr/local --without-x
make
sudo make install
sudo apt-get install libx11-dev libxt-dev
apt-cache search gcc | grep gcc-
apt-cache search g++ | grep g++-
sudo apt-get update
sudo apt-get install mlocate
locate app-defaults
sudo apt install locate
chmod +x ./path/to/local/run.sh
./run.sh
```
## Parameter of the .pla
- .i 14: Indicates that there are inputs.
- .o 8: Indicates that there are outputs.
- .ilb: Lists the labels for the input variables.
- .ob: Lists the labels for the output variables.
- .p 1028: Indicates the number of product terms (rows) in the PLA.

- "Real" The whole process takes about seconds in real-time.
- "User" time represents CPU time spent in in-process user mode (outside the core).
- "sys" time represents the time spent in the system (core).

- -o eqntott: This option tells Espresso to output the result in equation format.
- -Dexact: This directs Espresso to use the exact minimization algorithm.
- -Dqm: This directs Espresso to use the Quine-McCluskey minimization algorithm.

## BCD Seven Segment
![image](https://github.com/CTHMIT/Computer-Aided-Design/assets/107465888/4c7d8a50-f0ce-4c45-a3dd-03532755a576)
# Use espresso to simplify the two-level implementation of segments e and f. 
First ignore the Don't-care conditions (i.e., set the outputs to be 0 for input combinations 10 to 15), and then try to 
exploit the Don't-cares. 
![image](https://github.com/CTHMIT/Computer-Aided-Design/assets/107465888/9baeda42-cd88-4cb0-88e1-c05784d94b27)
## PLA
![image](https://github.com/CTHMIT/Computer-Aided-Design/assets/107465888/c8a744bc-0a0d-4434-984e-f52667edeb8c)



