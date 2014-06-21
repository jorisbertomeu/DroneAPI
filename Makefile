ALL	:	
		make -C ./api
		make -C ./mycode

gui	:	
		make -C ./api
		make -C ./gui

clean :
		make -C ./api clean
		make -C ./mycode clean
		make -C ./gui clean