if [ ! -d "result" ]; then
  mkdir result
fi

rm result/*

if [ -f "$src/main" ]; then
  rm src/main
fi

g++ -std=c++11 -o src/main src/main.cpp
./src/main data/digitstra.txt data/digitstest.txt

gnuplot result.plt