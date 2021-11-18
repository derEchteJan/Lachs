:: Runs cmake for Windows/Visual Stuido 
:: -A Architecture x64
:: -S Source Directory ./src
:: -B 'Build' Directory ./out (only the cmake cache and VS Solution will be there)
cmake -G "Visual Studio 15 2017" -A x64 -S %CD%\src -B %CD%\out\build_x64