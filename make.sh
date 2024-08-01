
build=false
run=""
test="DC_NO_TEST_CONTEXT"
local_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# while getopts "brX" o
# do
#     eval nextopt=\${$OPTIND}
#     case "${o}" in
#         X) echo "noval";;
#         b) echo "_Build";;
#         r) 
#             if [[ -n "$nextopt && $nextopt != -*" ]]; then
#                 OPTIND=$((OPTIND + 1))
#                 run=$nextopt
#             fi
#             echo "_Run $run"
#     esac
# done

while getopts br:Tt: flag
do 
    case "${flag}" in
        b) build=true;;
        r) run=${OPTARG};;
        t) test=${OPTARG};;
        T) test=""
    esac
done

echo "Build? " $build
echo "Run? " $run
echo "Test? " $test

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


if [ "$test" != "DC_NO_TEST_CONTEXT" ] ; then
    if [ "$test" = "" ] ; then
        echo "Run all tests"

        cmake --build ./build/test
        ctest --test-dir "${local_path}/build"
    else
        echo "Run test: ${test}"
        ctest "${local_path}/build"
    fi

fi



