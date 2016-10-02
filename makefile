substitution_cipher: substitution_cipher.o
	gcc substitution_cipher.o -o cipher
substitution_cipher.o: substitution_cipher.c

test: encrypt_1 decrypt_1 diff_1 encrypt_2 decrypt_2 diff_2

encrypt_1:
	./cipher 1 FEATHER test_1.dat test_1.encrypted
decrypt_1:
	./cipher 2 FEATHER test_1.encrypted test_1.decrypted
diff_1:
	diff -s test_1.dat test_1.decrypted
encrypt_2:
	./cipher 1 SECOND test_2.dat test_2.encrypted
decrypt_2:
	./cipher 2 SECOND test_2.encrypted test_2.decrypted
diff_2:
	diff -s test_2.dat test_2.decrypted
