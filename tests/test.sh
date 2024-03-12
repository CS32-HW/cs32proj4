SCRIPT_PATH="${0%/*}"
if [ "$0" != "$SCRIPT_PATH" ] && [ "$SCRIPT_PATH" != "" ]; then
        cd $SCRIPT_PATH
fi

g32 ../src/HashMap.h testhashmap.cpp && ./a.out
g32 ../src/geodb.cpp testgeodb.cpp && ./a.out

rm a.out
