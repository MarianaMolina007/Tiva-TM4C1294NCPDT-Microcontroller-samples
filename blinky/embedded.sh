sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
sudo apt-get update
sudo apt-get install gcc-arm-embedded
cd
mkdir imt-322
mv SW-TM4C-2.2.0.295.exe imt-322/
mkdir ti_software
mv SW-TM4C-2.2.0.295.exe ti_software/
cd ti_software/
unzip SW-TM4C-2.2.0.295.exe 
cd examples/boards/ek-tm4c1294xl
cd blinky/
cd gcc/
rm *
cd ..
gedit Makefile
sudo apt install make
make
ls gcc/
echo "Completed" 