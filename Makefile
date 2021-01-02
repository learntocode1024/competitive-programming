all:
	echo "Hello 2021!"

clean-vscode:
	find problem -type d -name ".vscode" -exec rm -rf {} \; 2>/dev/null

sync: clean-vscode
	find problem -maxdepth 2 -mindepth 2 -type d -exec cp -r .vscode {} \;

