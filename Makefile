gesture_detect:gesture_detect.cpp PAJ7620U2.h gesture_detect.h
	g++ -Wall gesture_detect.cpp -o gesture_detect -lwiringPi -lpthread -lm `pkg-config --cflags --libs opencv`
clean:
	rm gesture_detect

