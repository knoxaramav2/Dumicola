
build=false
run=""
test="DC_NO_TEST_CONTEXT"
local_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
clean=false

while getopts br:Tt:C flag
do 
    case "${flag}" in
        b) build=true;;
        r) run=${OPTARG};;
        t) test=${OPTARG};;
        T) test="";;
        C) clean=true;;
    esac
done

#echo "Build? " $build
#echo "Run? " $run
#echo "Test? " $test

if [ "$clean" = true ] ; then
    echo "Cleaning..."
    cmake --build ${local_path}/src --target clean
    rm -r ${local_path}/build
fi

if [ "$build" = true ] ; then
    echo "BUILD START"
    cmake -B "${local_path}/build" -S ${local_path}/src -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release
    cmake --build ${local_path}/build --config Release
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
        ctest --test-dir "${local_path}/build" --output-on-failure --verbose
    else
        echo "Run test: ${test}"
        ctest "${local_path}/build"
    fi

fi



