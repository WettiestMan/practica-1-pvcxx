namespace std {
	extern "C" int printf(const char* format, ...);
}

int main(void) {
	std::printf("void\n");
	return 0;
}  
