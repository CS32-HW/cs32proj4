SCRIPT_PATH="${0%/*}"
if [ "$0" != "$SCRIPT_PATH" ] && [ "$SCRIPT_PATH" != "" ]; then
        cd $SCRIPT_PATH
fi

set -e

g32 ../src/HashMap.h testhashmap.cpp && ./a.out
g32 ../src/geodb.cpp testgeodb.cpp && ./a.out
g32 testrouter.cpp ../src/geodb.cpp ../src/router.cpp && ./a.out

rm a.out
