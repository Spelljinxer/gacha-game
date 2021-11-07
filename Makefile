#@author Reiden Rufin
PROJECT = gacha
HEADERS = $(PROJECT).h 
OBJ = gacha.o 

C11    =  cc -std=c11
CFLAGS =  -Wall -Werror

$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ) 

gacha.o : gacha.c $(HEADERS)
	$(C11) $(CFLAGS) -c gacha.c
%.o : %.c $(HEADERS)
	$(C11) $(CFLAGS) -c $<
clean:
	rm -f $(PROJECT) $(OBJ
