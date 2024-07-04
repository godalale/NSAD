g++ -o logcomparison logcomparison.cpp `root-config --cflags --libs` -I/Users/alexandergodal/pythia8312/include -L/Users/alexandergodal/pythia8312/lib -lpythia8 && ./logcomparison
g++ -o comparison comparison.cpp `root-config --cflags --libs` -I/Users/alexandergodal/pythia8312/include -L/Users/alexandergodal/pythia8312/lib -lpythia8 && ./comparison
