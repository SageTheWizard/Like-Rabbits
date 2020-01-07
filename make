#!/bin/bash

CC='g++'
ENV='./src/enviorment.cxx'
RAB='./src/rabbit.cxx'
DRV='./src/driver.cxx'
LOG='./src/rabbit_log.cxx'

TARGET='rabbits'

rm ${TARGET}

eval "${CC} ${DRV} ${LOG} ${ENV} ${RAB} -o ${TARGET}"

