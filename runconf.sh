echo "Compiling program"
g++ -o program program.cpp `root-config --cflags --libs` -I/Users/alexandergodal/pythia8312/include -L/Users/alexandergodal/pythia8312/lib -lpythia8
echo "Running config00"
./program config00.conf config00.root > config00.out
echo "Running config01"
./program config01.conf config01.root > config01.out
echo "Running config10"
./program config10.conf config10.root > config10.out
echo "Running config11"
./program config11.conf config11.root > config11.out
