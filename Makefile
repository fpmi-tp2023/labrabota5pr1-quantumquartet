program: main.o menu.o manager.o owner.o jockey.o update.o insert.o delete.o sqlite3.o
	mkdir bin
	g++ -o bin/program obj/main.o obj/manager.o obj/owner.o obj/jockey.o obj/update.o obj/insert.o obj/delete.o obj/menu.o obj/sqlite3.o

main.o: src/main.cpp include/menu.h
	mkdir obj
	g++ -c src/main.cpp -o obj/main.o -lsqlite3
	
sqlite3.o: src/sqlite3.c include/sqlite3.h
	gcc -c src/sqlite3.c -o obj/sqlite3.o -lsqlite3	
	
menu.o: src/menu.cpp include/menu.h
	g++ -c src/menu.cpp -o obj/menu.o -lsqlite3

manager.o: src/manager.cpp include/manager.h
	g++ -c src/manager.cpp -o obj/manager.o -lsqlite3

owner.o: src/owner.cpp include/owner.h
	g++ -c src/owner.cpp -o obj/owner.o -lsqlite3

jockey.o: src/jockey.cpp include/jockey.h
	g++ -c src/jockey.cpp -o obj/jockey.o -lsqlite3

update.o: src/update.cpp include/update.h
	g++ -c src/update.cpp -o obj/update.o -lsqlite3

insert.o: src/insert.cpp include/insert.h
	g++ -c src/insert.cpp -o obj/insert.o -lsqlite3

delete.o: src/delete.cpp include/delete.h
	g++ -c src/delete.cpp -o obj/delete.o -lsqlite3

clean:
	rm -f obj/*.o bin/Program

run: 
	./bin/program