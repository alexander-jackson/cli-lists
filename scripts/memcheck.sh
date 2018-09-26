docker_image_name="dockerimage"
executable="main"
arguments="new list"

read -r -d '' COMMANDS << EOM
	cd /test/;
	make clean debug;
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$executable $arguments;
EOM

docker run -ti -v $PWD:/test $docker_image_name bash -c "$COMMANDS"
make clean build
