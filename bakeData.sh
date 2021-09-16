DIR_DATA_SOURCE=".\data"
DIR_X64=".\build\x64"
DIR_X32=".\build\x86"
DIR_PRJ=".\prj"

DIR_DATA_X64=".\build\x64\data"
DIR_DATA_X32=".\build\x86\data"
DIR_DATA_PRJ=".\prj\data"

# echo $DIR_SOURCE

rm -rf $DIR_DATA_X64 
cp -rf $DIR_DATA_SOURCE $DIR_X64

rm -rf $DIR_DATA_X32 
cp -rf $DIR_DATA_SOURCE $DIR_X32

rm -rf $DIR_DATA_PRJ 
cp -rf $DIR_DATA_SOURCE $DIR_PRJ
