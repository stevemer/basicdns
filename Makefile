server: server.cc
	g++ server.cc -o server

client: client.cc
	g++ client.cc -o client

clean:
	rm server client
