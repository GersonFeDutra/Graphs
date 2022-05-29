if [ ! -d .bin ]; then
	mkdir .bin
fi

echo "Choose compiler:"
echo "0 - gcc"
echo "1 - clang"
read -p ">> " opt

// TODO
if [[ "$opt" == "1" ]]; then
	echo "Building with clang"
else
	echo "Building with gcc"
fi
