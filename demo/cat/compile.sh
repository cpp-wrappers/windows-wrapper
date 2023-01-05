dir=`dirname ${BASH_SOURCE[0]}`
root=${dir}/../../
mkdir -p ${dir}/build

clang++ \
	-std=c++20 \
	-municode \
	-I${root}/../core/include \
	-I${root}/include \
	-o ${dir}/build/cat \
	${dir}/cat.cpp
