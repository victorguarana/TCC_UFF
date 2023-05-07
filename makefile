compile:
	cd models; \
	g++ -c car_stop.cpp -o car_stop.o &\
	g++ -c drone_stop.cpp -o drone_stop.o &\
	g++ -c flight.cpp -o flight.o &\
	g++ -c point.cpp -o point.o &\
	g++ -c route.cpp -o route.o &\
	cd vehicles; \
	g++ -c car.cpp -o car.o &\
	g++ -c drone.cpp -o drone.o &\
	g++ -c vehicle.cpp -o vehicle.o &\
	cd ../.. ; \

run:
	g++ main.cpp ./models/car_stop.o ./models/drone_stop.o ./models/flight.o ./models/point.o ./models/route.o ./models/vehicles/car.o ./models/vehicles/drone.o ./models/vehicles/vehicle.o
