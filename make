#!/bin/bash

CC='g++'
ENV='./src/enviorment.cxx'
RAB='./src/rabbit.cxx'
DRV='./src/driver.cxx'

TARGET='rabbits'

rm ${TARGET}

eval "${CC} ${DRV} ${ENV} ${RAB} -o ${TARGET}"

