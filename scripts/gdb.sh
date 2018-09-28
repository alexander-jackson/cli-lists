docker_image_name="dockerimage"
docker_options="--cap-add=SYS_PTRACE --security-opt seccomp=unconfined"
executable="lists"

read -r -d '' COMMANDS << EOM
	cd /test/;
	make clean debug;
	gdb $executable;
EOM

docker run $docker_options -ti -v $PWD:/test $docker_image_name bash -c "$COMMANDS"
make clean build
