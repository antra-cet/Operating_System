build:
	gcc tema1.c tema1_functions.c -g -o tema

clean:
	rm tema

checker:
	python3 checker.py
