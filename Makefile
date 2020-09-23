server: http_conn.cpp main.cpp                                    
	g++ http_conn.cpp main.cpp -I include -o server -lpthread
clean:
	rm *.o server
