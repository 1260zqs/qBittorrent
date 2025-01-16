cmake -B build -DCMAKE_BUILD_TYPE=Release -DGUI=OFF
cd build
cmake --build build -- -j 16
