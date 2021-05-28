# Q1
def q1(lst):
    return len(list(filter(lambda x: len(x) >= 2, [set([type(m) for m in x]) for x in lst])))


# Q2
def q2():
    vlst = ['x' + str(num) for num in range(10)]
    lamdic = {}
    for i, l in enumerate(vlst):
        lamdic[l] = (lambda x, y=i + 1: x * y)
    for v in vlst:
        for i in range(1, len(vlst) + 1):
            print(lamdic[v](i), end=' ')
        print()


# Q3
class a:

    def __init__(self, y):
        self.y = y

    def __call__(self, z):
        if z > self.y:
            return z - self.y
        else:
            return self.y - z


class b(a):

    def __call__(self, z=4):
        if z > self.y:
            return z - self.y
        else:
            return self.y - z


# Q4
def q4(nums):
    # There are 2 versions for this First one is using 1 variable and 1 loop,
    # and second one using no variables and 2 loops
    i = 0
    while i < len(nums) - 1:

        if nums[i] > nums[i + 1]:
            nums[i], nums[i + 1] = nums[i + 1], nums[i]
            i = 0
        else:
            i += 1

    # for i in range(len(nums) - 1):
    # for j in range(0, len(nums) - i - 1):
    # if nums[j] > nums[j+1]:
    # nums[j], nums[j+1] = nums[j+1], nums[j]


# Q5
def q5(func):
    count = 0

    def wrapper(*args, **kw):
        global allCount
        global types_dict
        nonlocal count
        parameters = 0

        allCount += 1
        count += 1
        parameters += len(args) + len(kw)

        val = func(*args, **kw)
        type_name = type(val).__name__
        if type_name in types_dict:
            types_dict[type_name] += 1
        else:
            types_dict[type_name] = 1

        print(func.__name__, "called", count, "times")
        print(func.__name__, "have", parameters, "parameters")
        print("All functions called", allCount, "times")
        print("Types:", types_dict)
        print()
        return val

    return wrapper


@q5
def func1(a1):
    return a1


@q5
def func2(a2, b2):
    return a2


@q5
def func3(a3, b3, c3):
    return a3


# Q6

class Pizza(object):
    def get_ingredients(self):
        return ''

    def get_calories(self):
        return 0


class Pizza_Decorator(Pizza):

    def __init__(self, decorated_pizza):
        self.decorated_pizza = decorated_pizza

    def get_calories(self):
        return self.decorated_pizza.get_calories()

    def get_ingredients(self):
        return self.decorated_pizza.get_ingredients()


class Cheese(Pizza_Decorator):

    def __init__(self, decorated_pizza, item):
        Cheese_types = {"Mozzarella": 50, "Cheese": 30, "Parmesan": 60, "Vegan": 20}
        self.calorie = Cheese_types[item]
        self.item = item
        Pizza_Decorator.__init__(self, decorated_pizza)

    def get_calories(self):
        return self.decorated_pizza.get_calories() + self.calorie

    def get_ingredients(self):
        return self.decorated_pizza.get_ingredients() + self.item + ', '


class Dough(Pizza_Decorator):

    def __init__(self, decorated_pizza, item):
        Dough_types = {"Thick": 50, "Thin": 30, "Gluten_Free_Thick": 60, "Gluten_Free_Thin": 20}
        self.calorie = Dough_types[item]
        self.item = item
        Pizza_Decorator.__init__(self, decorated_pizza)

    def get_calories(self):
        return self.decorated_pizza.get_calories() + self.calorie

    def get_ingredients(self):
        return self.decorated_pizza.get_ingredients() + self.item + ', '


class Sauce(Pizza_Decorator):

    def __init__(self, decorated_pizza, item):
        Sauce_types = {"Tomato": 50, "Roze": 30, "Spinchcream": 60, "Pesto": 20}
        self.calorie = Sauce_types[item]
        self.item = item
        Pizza_Decorator.__init__(self, decorated_pizza)

    def get_calories(self):
        return self.decorated_pizza.get_calories() + self.calorie

    def get_ingredients(self):
        return self.decorated_pizza.get_ingredients() + self.item + ', '


class Toppings(Pizza_Decorator):

    def __init__(self, decorated_pizza, item):
        Toppings_types = {"Olives": 50, "Corn": 30, "Tomato": 60, "Onion": 20}
        self.calorie = Toppings_types[item]
        self.item = item
        Pizza_Decorator.__init__(self, decorated_pizza)

    def get_calories(self):
        return self.decorated_pizza.get_calories() + self.calorie

    def get_ingredients(self):
        return self.decorated_pizza.get_ingredients() + self.item


print("Question 1")
lst = [[1, 5, 3], ['a', 'v', 3], ["sss", 'b'], [], [[3, 4, 5], ['a']], [(4, 5, 6), [4, 5, 6]]]
print(q1(lst))
print()
print("Question 2")
q2()
print()
print("Question 3")
print(a(5)(b(6)()))
print(a(6)(b(5)(6)))
print()
print("Question 4")
num = [1, 5, 7, 4, 2, 6, 9, 3]
q4(num)
print(num)
print()
print("Question 5")
allCount = 0
types_dict = {}
func1(1)
func3(('c', 3), ('a', 1), ("rawr", 3, 7))
func1(2)
func2('woof', 'meow')
func1(3)
func3(('d', 4), (2, 'b'), (5, 'k'))
func1(4)
print()
print("Question 6")
myPizza = Pizza()
myPizza = Dough(myPizza, "Thick")
myPizza = Cheese(myPizza, "Parmesan")
myPizza = Sauce(myPizza, "Tomato")
myPizza = Toppings(myPizza, "Onion")
print("Calorie Number:", myPizza.get_calories(), " Ingredients:", myPizza.get_ingredients())
print()
