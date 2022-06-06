#!/bin/bash
x=""
y=""

if [[ $1 == 1 ]];then
    x=${x:-4}
    y=${y:-1}
else
    x=${x:-1}
    y=${y:-4}
fi

echo sed -E -i "s/Mod${x}Mask/Mod${y}Mask/" config.def.h
f(){
    sleep 1
    sed -E -i "s/Mod${x}Mask/Mod${y}Mask/" config.def.h
    make install && pkill dwm
}

f
