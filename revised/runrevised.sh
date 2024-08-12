echo "Compiling program"
g++ -o revision revision.cpp `root-config --cflags --libs` -I/Users/alexandergodal/pythia8312/include -L/Users/alexandergodal/pythia8312/lib -lpythia8
echo "Running config00"
./revision ../config00.conf revision00.root > revision00.out
echo "Running config01"
./revision ../config01.conf revision01.root > revision01.out
echo "Running config10"
./revision ../config10.conf revision10.root > revision10.out
echo "Running config11"
./revision ../config11.conf revision11.root > revision11.out
