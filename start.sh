#!/bin/bash
sudo ./a.out 1
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out 1
    sudo ./a.out 1
    sudo ./a.out 1
    sudo ./a.out 1
    sudo ./a.out 1
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out 2
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out 2
    sudo ./a.out 2
    sudo ./a.out 2
    sudo ./a.out 2
    sudo ./a.out 2
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out 3
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out 3
    sudo ./a.out 3
    sudo ./a.out 3
    sudo ./a.out 3
    sudo ./a.out 3
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out 4
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out 4
    sudo ./a.out 4
    sudo ./a.out 4
    sudo ./a.out 4
    sudo ./a.out 4
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out 5
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out 5
    sudo ./a.out 5
    sudo ./a.out 5
    sudo ./a.out 5
    sudo ./a.out 5
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out 6
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out 6
    sudo ./a.out 6
    sudo ./a.out 6
    sudo ./a.out 6
    sudo ./a.out 6
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out 7
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out 7
    sudo ./a.out 7
    sudo ./a.out 7
    sudo ./a.out 7
    sudo ./a.out 7
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out 8
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out 8
    sudo ./a.out 8
    sudo ./a.out 8
    sudo ./a.out 8
    sudo ./a.out 8
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out 9
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out 9
    sudo ./a.out 9
    sudo ./a.out 9
    sudo ./a.out 9
    sudo ./a.out 9
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out a
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out a
    sudo ./a.out a
    sudo ./a.out a
    sudo ./a.out a
    sudo ./a.out a
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out b
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out b
    sudo ./a.out b
    sudo ./a.out b
    sudo ./a.out b
    sudo ./a.out b
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
sudo ./a.out c
if [ $? -ne 0 ]; then
    echo "failed"
    sudo ./a.out c
    sudo ./a.out c
    sudo ./a.out c
    sudo ./a.out c
    sudo ./a.out c
    if [ $? -ne 0 ]; then
        exit
    else
        echo "succeed"
    fi
else
    echo "succeed"
fi
sleep 1
