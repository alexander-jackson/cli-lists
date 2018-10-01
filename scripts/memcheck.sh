docker_image_name="dockerimage"
executable="lists"
arguments="$@"

read -r -d '' COMMANDS << EOM
	mkdir -p ~/.local/share/cli-lists/
	touch ~/.local/share/cli-lists/lists.toml
	cd /test/;
	make clean debug;
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$executable $arguments;
EOM

docker run -ti -v $PWD:/test $docker_image_name bash -c "$COMMANDS"
make clean build
