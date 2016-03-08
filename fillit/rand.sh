rm -f sample.fillit
./tetri-gen -v -f $1
cat sample.fillit
time ./fillit sample.fillit