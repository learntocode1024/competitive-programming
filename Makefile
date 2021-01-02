all: sync update

clean: clean-vscode

clean-vscode:
	find problem -type d -name ".vscode" -exec rm -rf {} \; 2>/dev/null | true

sync: 
	find problem -maxdepth 2 -mindepth 2 -type d -exec cp -r .vscode {} \;

update:
	./helper/parse_template.sh
