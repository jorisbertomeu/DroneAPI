ALL	:	
		make -C ./api
		make -C ./mycode

clean :
		make -C ./api clean
		make -C ./mycode clean