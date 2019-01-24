particle compile electron ../Particle --saveTo firmware.bin
if [ $? -eq 0 ]; then
particle flash --serial firmware.bin
    echo OK
else
    echo FAIL
fi
