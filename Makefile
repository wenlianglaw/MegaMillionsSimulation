all:	main

N?=20
VERBOSE?=


main:
	g++ mega_millions_simulation.cpp -o mega_millions_simulation --std=c++17 -O3

run:	main exec clean

exec:
	./mega_millions_simulation -n $N $(VERBOSE)

clean:
	@echo "Cleaning hard..."
	@sleep 0.`date +"%S"`
	@echo "Clean finished."
