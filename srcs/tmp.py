
patt_data_str = """1	2	3	4
2	1	3	4
1	3	2	4
2	3	1	4
3	1	2	4
3	2	1	4
1	2	4	3
2	1	4	3
1	3	4	2
2	3	4	1
3	1	4	2
3	2	4	1
1	4	2	3
2	4	1	3
1	4	3	2
2	4	3	1
3	4	1	2
3	4	2	1
4	1	2	3
4	2	1	3
4	1	3	2
4	2	3	1
4	3	1	2
4	3	2	1"""
op_data_str = """iv											
sa											
ra	sa	rra									
ra	sa	rra	sa								
sa	ra	sa	rra								
sa	ra	sa	rra	sa							
ra	ra	sa	rra	rra							
sa	ra	ra	sa	rra	rra						
ra	ra	sa	rra	sa	rra						
ra	ra	sa	rra	sa	rra	sa					
sa	ra	ra	sa	rra	sa	rra					
sa	ra	ra	sa	rra	sa	rra	sa				
ra	sa	ra	sa	rra	rra						
ra	sa	ra	sa	rra	sa						
ra	sa	ra	sa	rra	sa	rra					
ra	sa	ra	sa	rra	sa	rra	sa				
ra	sa	rra	sa	ra	ra	sa	rra	sa	rra		
ra	sa	ra	sa	rra	sa	rra	sa	ra	sa	rra	
sa	ra	sa	ra	sa	rra	rra					
sa	ra	sa	ra	sa	rra	rra	sa				
sa	ra	sa	ra	sa	rra	sa	rra				
sa	ra	sa	ra	sa	rra	sa	rra	sa			
sa	ra	sa	ra	sa	rra	rra	sa	ra	sa	rra	
sa	ra	sa	rra	sa	ra	ra	sa	rra	sa	rra	sa"""

op_data = [line.split('\t') for line in op_data_str.split('\n')]
patt_data = [line.split('\t') for line in patt_data_str.split('\n')]

print(op_data)

def print_ops_table():
	for line in op_data:
		l = ['OP_IV' if e == '' else 'OP_' + e.upper() for e in line]
		print('\t' + ', '.join(l[0:8]) + ',')
		print('\t' + ', '.join(l[8:]) + ',')

def print_len_table():
	for line in op_data:
		count = sum(0 if e == '' or e == 'iv' else 1 for e in line)
		print('\t' + str(count) + ',')

def print_pattern():
	for line in patt_data:
		print('\t' + ', '.join(line) + ',')

#print_ops_table()
#print_len_table()
print_pattern()
