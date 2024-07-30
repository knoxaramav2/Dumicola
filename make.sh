
build=false
run=""
local_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

while getopts br: flag
do 
    case "${flag}" in
        b) build=true;;
        r) run=${OPTARG};;
    esac
done

echo "Build? " $build
echo "Run? " $run

if [ "$build" = true ] ; then
    echo "BUILD START"
    cmake -B "${local_path}/build" -S ${local_path}/src -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release
    cmake --build "${local_path}/build" --config Release
    echo "DONE."
fi

if [ "$run" != "" ] ; then
    exec_dir="${local_path}/build/${run}/${run}"
    ${exec_dir}
fi




