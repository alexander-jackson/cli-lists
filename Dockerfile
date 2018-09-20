FROM ubuntu:16.04

RUN apt-get update && apt-get upgrade -y && apt-get install gcc valgrind build-essential -y
