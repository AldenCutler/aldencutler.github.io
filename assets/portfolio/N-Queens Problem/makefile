queens: isLegalPosition.o nextLegalPosition.o firstSolution.o allSolutions.o tests.o queens.o
	gcc -g -Wall isLegalPosition.o nextLegalPosition.o firstSolution.o allSolutions.o tests.o queens.o -lm -o queens.exe
	./queens.exe
isLegalPosition.o: functions.h isLegalPosition.c
	gcc -g -Wall -c isLegalPosition.c
nextLegalPosition.o: functions.h nextLegalPosition.c
	gcc -g -Wall -c nextLegalPosition.c
firstSolution.o: functions.h firstSolution.c
	gcc -g -Wall -c firstSolution.c
allSolutions.o: functions.h allSolutions.c
	gcc -g -Wall -c allSolutions.c
tests.o: functions.h tests.c
	gcc -g -Wall -c tests.c
queens.o: functions.h queens.c
	gcc -g -Wall -c queens.c
clean:
	del -f *.o *.exe