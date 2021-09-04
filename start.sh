read -p "Compile ? " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    cd build
     
    make

    cd ..
fi

read -p "Run ? " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    cd build
     
    ./You_bot

    cd ..
fi