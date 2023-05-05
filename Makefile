build:
	@gcc main.c json.c

run: build
	@echo "" && echo "" && echo ""
	@./a.out