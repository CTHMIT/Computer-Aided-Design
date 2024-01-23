
## main sis to install

  sudo dpkg -i sis.deb
  sudo apt install -y make gcc bison flex build-essential
  export CFLAGS=-std=gnu90

##Additional libraries (if needed):
  ./configure prefix=/usr/local --without-x
  make
  sudo make install
  sudo apt-get install libx11-dev libxt-dev
  apt-cache search gcc | grep gcc-
  apt-cache search g++ | grep g++-
  sudo apt-get update
  sudo apt-get install mlocate
  locate app-defaults
  sudo apt install plocate

## Parameter of the .pla
.i 14: Indicates that there are inputs.
.o 8: Indicates that there are outputs.
.ilb: Lists the labels for the input variables.
.ob: Lists the labels for the output variables.
.p 1028: Indicates the number of product terms (rows) in the PLA.

"Real" The whole process takes about seconds in real time.
"User" time represents CPU time spent in in-process user mode (outside the core).
"sys" time represents the time spent in the system (core).

-o eqntott: This option tells Espresso to output the result in equation format.
-Dexact: This directs Espresso to use the exact minimization algorithm.
-Dqm: This directs Espresso to use the Quine-McCluskey minimization algorithm.


## Set the run file
  nano ~/.bashrc
  alias autorun='/path/to/your/run.sh'
  source ~/.bashrc
