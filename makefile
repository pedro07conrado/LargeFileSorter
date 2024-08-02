
CXX = g++
CXXFLAGS = -g -Wall


gerar_arquivo: gerar_arquivo.cpp big_file.cpp BufferEntrada.cpp BufferSaida.cpp
	$(CXX) $(CXXFLAGS) gerar_arquivo.cpp big_file.cpp BufferEntrada.cpp BufferSaida.cpp -o gerar_arquivo


clean:
	rm -f gerar_arquivo