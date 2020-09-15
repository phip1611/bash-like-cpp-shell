# runs a single test from the build directory; test binary name passed as first argument

echo "running test '$1':"
./build/$1
