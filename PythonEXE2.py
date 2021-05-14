# Fill in the functions content & think about the return values. (Don't forget to remove the 'pass' statement)
# In questions with classes you can create the class & write the logic inside the function.

# Class
def q1a(input_num):
	class PrimeSmallerThan:
		def __init__(self,max): # add parameters
			self.current = 1
			self.max = max

		def __iter__(self):
			return self

		def __next__(self):
			self.current += 1
			if self.current >= self.max:
				raise StopIteration
			else:
				for divisor in range(2, self.current):
					if self.current % divisor == 0:
						self.current += 1
						if self.current >= self.max:
							raise StopIteration
				return self.current

	instance = PrimeSmallerThan(input_num) # add parameters
	return instance

# Generator
def q1b(input_num):
	while input_num > 0:
		if checkprime(input_num):
			yield input_num
		input_num-=1

def check_prime(num):
	flag = True
	if num > 1:
		for i in range(2,num):
			if num % i == 0:
				flag = False
				break
	return flag
# List comprehension
def q2(n):
	lst = []
	for i in range(2,n):
		if (n % i) == 0:
			lst.append(i)
	return lst
# One line
# m - min, n - max
def q3(m, n):
	return ["no prime" if not check_prime(i) else "prime" for i in range(m,n)]

# Generator
# m - min, n - max
def q4(m, n):
	for i in range(m,n):
		if i % 2 == 0:
			first = int(i % 10)
			second = int(i / 10)
			#if first != 0:
			if first/second % 1 == 0:
				yield i
# One line
def q5(str):
	return dict(zip(''.join(str.split(' ')), [str.count(i) for i in ''.join(str.split(' '))]))

# Generator
def q6a(str1, str2):
	for x,y in zip(str1,str2):
		if x == y:
			yield x

# Class
def q6b(str1, str2):
	class StringsCompare: # add class functions
		def __init__(self, st1 , st2):
			self.current = 0
			self.st1 = str1
			self.st2 = str2

		def __iter__(self):
			return self

		def __next__(self):
			if self.current >= len(self.st1) or self.current >= len(self.st2):
				raise StopIteration
			else:
				while self.current != len(self.st1) or self.current != len(self.st2):
					if self.st1[self.current] == self.st2[self.current]:
							self.current += 1
							return self.st1[self.current-1]
					self.current += 1

	instance = StringsCompare(str1,str2) # add parameters
	return instance

# One line
def q7(char_list, index_list):
	return  ''.join(char_list[i-1] for i in index_list)

# Generator
def q8a(a, b):
	while 1:
		for x in range(a, b):
			yield x

		for y in range (b, a, -1):
			yield y


# q8a with user_choice
def q8b(a, b):
	direction = 1
	number = a - 1
	while True:
		number += direction

		while a <= number <= b:

			x = yield number
			if x is not None:
				direction = 1 if int(x) > 0 else -1
			else:
				number += direction
		else:
			print()
			direction = -direction


def processor():
	while True:
		value = yield
		print(f'Processing {value}')


data_processor = processor()

print(type(data_processor))

data_processor.send(None)

for x in range(1, 5):
	data_processor.send(x)

# Remove the '#' to run the corresponding test
# Don't forget to fill in the parameters.
if __name__ == "__main__":

	# q1a #
	 #input_num = 100
	 #for num in q1a(input_num):
	# 	print(num)

	# q1b #
	#for num in q1b(100):
	#	print(num)

	# q2 #
	#print(q2(60))

	# q3 #
	#print(q3(2, 14))

	# q4 #
	 #for c in q4(12, 45):
	 	#print(c)

	# q5 #
	#print(q5("this is a simple string"))
	
	# q6a #
	#for c in q6a("like", "love"):
	#	print(c)

	# q6b #
	#for c in q6b("like", "love"):
	#	print(c)
	
	# q7 #
	#print(q7(['a', 'h', 'f', 'e', 'y', 'u'], [1, 5, 3, 6, 2, 4]))
	
	# q8a #
	#for c in q8a(3,11):
	#	print(c)

	# q8b #
	processor()