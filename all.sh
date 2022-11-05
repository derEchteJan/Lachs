# Read config file config_lin.txt
source config_lin.txt
echo QT_BASE: $QT_BASE
echo BUILD_DIR: $BUILD_DIR
# Generate
cmake --version
cmake -DQT_BASE=$QT_BASE -S src -B $BUILD_DIR
# Build
cmake --build $BUILD_DIR
# Run
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$QT_BASE/bin
echo running $BUILD_DIR/Lachs
$BUILD_DIR/Lachs