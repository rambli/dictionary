
default:
	gcc trie.c reader.c -o dictionary

clean:
	rm dictionary
